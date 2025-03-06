#include "websocket/stringsubscribeclient.h"
#include <QJsonDocument>

StringSubscribeClient::StringSubscribeClient(const QString &serverAddress, const QString &topic, QObject *parent)
    : SubscribeClient(serverAddress, parent), mTopic(topic) {}

void StringSubscribeClient::subscribe() {
    QJsonObject jsonObj;
    jsonObj["op"] = "subscribe";
    jsonObj["type"] = "std_msgs/String";
    jsonObj["topic"] = mTopic; // Gán trực tiếp mTopic
    mWebSocket->sendTextMessage(QJsonDocument(jsonObj).toJson());
}

void StringSubscribeClient::processMessage(const QString &topic, const QJsonObject &msgObj) {
    if (msgObj.contains("data")) {
        mData[topic] = msgObj["data"].toString();
    }
}