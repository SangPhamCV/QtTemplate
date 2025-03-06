#ifndef PUBLISHCLIENT_H
#define PUBLISHCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QJsonObject>
#include <QMap>
#include <QVariant>

class PublishClient : public QObject {
    Q_OBJECT

public:
    explicit PublishClient(const QString &serverAddress, QObject *parent = nullptr);
    virtual ~PublishClient();

    void start();
    void publish(const QVariant &message);

protected:
    virtual QString formatMessage(const QVariant &message) = 0; // Class con định dạng message

private slots:
    void onConnected();
    void onDisconnected();

private:
    QWebSocket *mWebSocket;
    QString mServerAddress;
};

#endif // PUBLISHCLIENT_H