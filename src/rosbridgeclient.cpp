// #include "rosbridgeclient.h"
// #include <QDebug>

// RosBridgeClient::RosBridgeClient(QObject *parent) : QObject(parent) {}

// RosBridgeClient::~RosBridgeClient() {
//     qDeleteAll(mStringClients);
//     qDeleteAll(mPoseClients);
// }

// void RosBridgeClient::addStringClient(const QString &topic) {
//     if (!mStringClients.contains(topic)) {
//         StringSubscribeClient* client = new StringSubscribeClient(mServerAddress, topic, this);
//         mStringClients[topic] = client;
//         connect(client, &StringSubscribeClient::dataChanged, this, [this, topic]() {
//             mTopicData[topic] = getStringData(topic);
//             emit topicDataChanged();
//         });
//         client->start();
//     }
// }

// void RosBridgeClient::addPoseClient(const QString &topic) {
//     if (!mPoseClients.contains(topic)) {
//         PoseSubscribeClient* client = new PoseSubscribeClient(mServerAddress, topic, this);
//         mPoseClients[topic] = client;
//         connect(client, &PoseSubscribeClient::dataChanged, this, [this, topic]() {
//             mTopicData[topic] = getPoseData(topic);
//             emit topicDataChanged();
//         });
//         client->start();
//     }
// }

// QVariant RosBridgeClient::getStringData(const QString &topic) const {
//     if (mStringClients.contains(topic)) {
//         QMap<QString, QVariant> data = mStringClients[topic]->data();
//         return data.value(topic, "No data");
//     }
//     return "No data";
// }

// QVariant RosBridgeClient::getPoseData(const QString &topic) const {
//     if (mPoseClients.contains(topic)) {
//         QMap<QString, QVariant> data = mPoseClients[topic]->data();
//         return data.value(topic, QVariantMap());
//     }
//     return QVariantMap();
// }

#include "rosbridgeclient.h"
#include <QJsonDocument>
#include <QDebug>

RosBridgeClient::RosBridgeClient(QObject *parent) : QObject(parent) {
    connect(&mWebSocket, &QWebSocket::connected, this, &RosBridgeClient::onConnected);
    connect(&mWebSocket, &QWebSocket::textMessageReceived, this, &RosBridgeClient::onMessageReceived);

    // Khai báo các topic và kiểu dữ liệu
    mTopics["/cmd_vel"] = "geometry_msgs/Twist";
    mTopics["/amcl_pose"] = "geometry_msgs/PoseWithCovarianceStamped";
    mTopics["/battery_status"] = "std_msgs/Float32";
    mTopics["/laser_scan"] = "sensor_msgs/LaserScan";
    mTopics["/goal_position"] = "std_msgs/Float32MultiArray";
    mTopics["/move_command"] = "std_msgs/String";
    mTopics["/waypoints"] = "geometry_msgs/PoseArray";
}

void RosBridgeClient::connectToRos() {
    mWebSocket.open(QUrl("ws://192.168.62.138:9090"));
}

void RosBridgeClient::onConnected() {
    qDebug() << "Connected to ROSBridge!";
    subscribeToAllTopics();
}

void RosBridgeClient::subscribeToAllTopics() {
    for (auto topic : mTopics.keys()) {
        QJsonObject msg;
        msg["op"] = "subscribe";
        msg["topic"] = topic;
        msg["type"] = mTopics[topic];
        mWebSocket.sendTextMessage(QJsonDocument(msg).toJson());
    }
}

void RosBridgeClient::publishToTopic(const QString &topic, const QJsonObject &message) {
    if (!mTopics.contains(topic)) {
        qWarning() << "Topic" << topic << "chưa được đăng ký.";
        return;
    }

    QJsonObject msg;
    msg["op"] = "publish";
    msg["topic"] = topic;
    msg["msg"] = message;
    mWebSocket.sendTextMessage(QJsonDocument(msg).toJson());
}

void RosBridgeClient::onMessageReceived(const QString &message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject obj = doc.object();
    if (obj.contains("topic") && obj.contains("msg")) {
        QString topic = obj["topic"].toString();
        emit receivedMessage(topic, obj["msg"].toObject());
    }
}
