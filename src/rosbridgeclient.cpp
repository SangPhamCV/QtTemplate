#include "rosbridgeclient.h"

RosBridgeClient::RosBridgeClient(QObject *parent) : QObject(parent) {
    connect(&mWebSocket, &QWebSocket::connected, this, &RosBridgeClient::onConnected);
    connect(&mWebSocket, &QWebSocket::textMessageReceived, this, &RosBridgeClient::onMessageReceived);

    // Define topic and datatype mapping
    mTopics["/armbot/mobile_base_controller/cmd_vel"] = "geometry_msgs/Twist";
    mTopics["/amcl_pose"] = "geometry_msgs/PoseWithCovarianceStamped";
    mTopics["/battery_status"] = "std_msgs/Float32";
    mTopics["/goal_position"] = "std_msgs/Float32MultiArray";
    mTopics["/move_command"] = "std_msgs/String";
    mTopics["/waypoints"] = "geometry_msgs/PoseArray";
    mTopics["/result_navigation"] = "std_msgs/String";
    mTopics["/hermite_path"] = "nav_msgs/Path";
    mTopics["/start_tracking"] = "std_msgs/String";
    mTopics["/estimate_distance"] = "std_msgs/Float32";
    mTopics["/remaining_distance"] = "std_msgs/Float32";
    mTopics["/done_tracking"] = "std_msgs/String";
    mTopics["/virtual"] = "geometry_msgs/PoseArray";
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
