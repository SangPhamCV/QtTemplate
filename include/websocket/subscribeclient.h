#ifndef SUBSCRIBECLIENT_H
#define SUBSCRIBECLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QJsonObject>
#include <QMap>
#include <QVariant>

class SubscribeClient : public QObject {
    Q_OBJECT

public:
    explicit SubscribeClient(const QString &serverAddress, QObject *parent = nullptr);
    virtual ~SubscribeClient();

    void start();
    QMap<QString, QVariant> data() const { return mData; }

signals:
    void dataChanged();

protected:
    virtual void subscribe() = 0;
    virtual void processMessage(const QString &topic, const QJsonObject &msgObj) = 0;

    QMap<QString, QVariant> mData;
    QWebSocket *mWebSocket; 

private slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void onDisconnected();

private:
    QString mServerAddress;
};

#endif // SUBSCRIBECLIENT_HH