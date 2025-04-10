#include "filehandler.h"

FileHandler::FileHandler(QObject *parent) : QAbstractListModel(parent) {
    QString defaultPath = QDir::currentPath() + "/../maps";
    loadFiles(defaultPath);
}

int FileHandler::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return mFileNames.size();
}

QVariant FileHandler::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    if (index.row() >= mFileNames.size()) return QVariant();

    if (role == FileNameRole) {
        return mFileNames[index.row()];
    }

    return QVariant();
}

QHash<int, QByteArray> FileHandler::roleNames() const {
    return {{FileNameRole, "fileName"}};  // Role name for QML
}

void FileHandler::loadFiles(const QString &folderPath) {
    QDir dir(folderPath);
    if (!dir.exists()) {
        qDebug() << "Directory does not exist:" << folderPath;
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

QStringList FileHandler::getFiles() const {
    return mFileNames;
}

