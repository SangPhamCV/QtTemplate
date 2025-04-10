#ifndef ROSBRIDGECLIENT_H
#define ROSBRIDGECLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QJsonObject>
#include <QJsonDocument>

class RosBridgeClient : public QObject {
    Q_OBJECT
public:
    explicit RosBridgeClient(QObject *parent = nullptr);

    void connectToRos();
    void subscribeToAllTopics();
    void publishToTopic(const QString &topic, const QJsonObject &message);
    
signals:
    void receivedMessage(const QString &topic, const QJsonObject &msg);

private slots:
    void onConnected();
    void onMessageReceived(const QString &message);

private:
    QWebSocket mWebSocket;
    QMap<QString, QString> mTopics;

};

#endif // ROSBRIDGECLIENT_H