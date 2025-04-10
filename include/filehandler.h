#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QVariant>
#include <QAbstractListModel>
#include <QDir>
#include <QDebug>

class FileHandler : public QAbstractListModel {
    Q_OBJECT

public:
    explicit FileHandler(QObject *parent = nullptr);

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

#endif // FILEHANDLER_H
