#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent) {}
FileListModel::FileListModel(QObject *parent) : QAbstractListModel(parent) {
    QString defaultPath = QDir::currentPath() + "/../maps";
    loadFiles(defaultPath);
}

void MainWindow::readYAML(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file from resource";
        return;
    }

    QByteArray fileData = file.readAll();
    YAML::Node node = YAML::Load(fileData.toStdString());

    mYamlData["image"] = QString::fromStdString(node["image"].as<std::string>());
    mYamlData["resolution"] = node["resolution"].as<double>();
    mYamlData["negate"] = node["negate"].as<int>();
    mYamlData["occupied_thresh"] = node["occupied_thresh"].as<double>();
    mYamlData["free_thresh"] = node["free_thresh"].as<double>();

    YAML::Node origin = node["origin"];
    QVariantList originList;
    for (std::size_t i = 0; i < origin.size(); i++) {
        originList.append(origin[i].as<double>());
    }
    mYamlData["origin"] = originList;
}


QVariantMap MainWindow::getYamlValue() const {
    return mYamlData;
}

int FileListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return mFileNames.size();
}

QVariant FileListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    if (index.row() >= mFileNames.size()) return QVariant();

    if (role == FileNameRole) {
        return mFileNames[index.row()];
    }

    return QVariant();
}

QHash<int, QByteArray> FileListModel::roleNames() const {
    return {{FileNameRole, "fileName"}};  // Role name for QML
}

void FileListModel::loadFiles(const QString &folderPath) {
    QDir dir(folderPath);
    if (!dir.exists()) {
        qDebug() << "Directory does not exist";
        return;
    }

    QStringList filters;
    filters << "*.yaml";
    dir.setNameFilters(filters);

    beginResetModel(); // Reset the model before updating
    mFileNames.clear();

    QStringList fileList = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    for (const QString &fileName : fileList) {
        mFileNames.append(fileName.left(fileName.length() - 5)); // delete ".yaml"
    }

    endResetModel(); // Notify QML to update the view
}

QStringList FileListModel::getFiles() const {
    return mFileNames;
}
