#include "websocket/posesubscribeclient.h"
#include <QJsonDocument>
#include <QVariant>
#include <QDebug>
#include <QtMath>

PoseSubscribeClient::PoseSubscribeClient(const QString &serverAddress, const QString &topic, QObject *parent)
    : SubscribeClient(serverAddress, parent), mTopic(topic) {}

void PoseSubscribeClient::subscribe() {
    QJsonObject jsonObj;
    jsonObj["op"] = "subscribe";
    jsonObj["type"] = "geometry_msgs/PoseWithCovarianceStamped";
    jsonObj["topic"] = mTopic; // Gán trực tiếp mTopic
    mWebSocket->sendTextMessage(QJsonDocument(jsonObj).toJson());
}

void PoseSubscribeClient::processMessage(const QString &topic, const QJsonObject &msgObj) {
    QVariantMap poseMap;
    QJsonObject poseOuter = msgObj.value("pose").toObject();
    QJsonObject poseInner = poseOuter.value("pose").toObject();
    QJsonObject position = poseInner.value("position").toObject();
    QJsonObject orientation = poseInner.value("orientation").toObject();

    poseMap["position_x"] = position.value("x").toDouble();
    poseMap["position_y"] = position.value("y").toDouble();
    poseMap["angular_yaw"] = 2.0 * qAtan2(orientation.value("z").toDouble(), orientation.value("w").toDouble());
    mData[topic] = poseMap;
}