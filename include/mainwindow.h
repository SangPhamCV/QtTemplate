#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <yaml-cpp/yaml.h>
#include <QDebug>
#include <QFile>
#include <QAbstractListModel>
#include <QDir>

class MainWindow : public QObject {
    Q_OBJECT

public:
    explicit MainWindow(QObject *parent = nullptr);

    Q_INVOKABLE void readYAML(const QString &filePath);
    Q_INVOKABLE QVariantMap getYamlValue() const;

private:
    QVariantMap mYamlData;
};

class FileListModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit FileListModel(QObject *parent = nullptr);

    enum {
        FileNameRole = Qt::UserRole + 1,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void loadFiles(const QString &folderPath);
    Q_INVOKABLE QStringList getFiles() const;

private:
    QStringList mFileNames;
};

#endif // MAINWINDOW_H

