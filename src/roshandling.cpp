#include "roshandling.h"

RosHandling::RosHandling(HermiteCurve* hermiteCurve, VirtualWall* virtualWall, QObject *parent) : QObject(parent), hermiteCurve(hermiteCurve), virtualWall(virtualWall) {
    connect(&mRosClient, &RosBridgeClient::receivedMessage, this, &RosHandling::updateRosDataReceived);
    mRosClient.connectToRos();

    goalPoints = {{
        {-3.0, 1.0, 90.0}, {-1.0, 1.0, 120.0}, {-4.0, 4.0, 30.0}, {-1.0, 4.0, 150.0}, {3.5, 4.0, -90.0},
        {1.0, 3.0, 0.0}, {6, 1.0, -60.0}, {-6.0, 3.5, 180.0}, {-6, 0.0, -45.0}, {-6.0, -3.0, -135.0}
    }};
}

void RosHandling::publishVelocityCommand(double linear_x, double angular_z) {
    QJsonObject twistMsg;
    twistMsg["linear"] = QJsonObject{{"x", linear_x}, {"y", 0.0}, {"z", 0.0}};
    twistMsg["angular"] = QJsonObject{{"x", 0.0}, {"y", 0.0}, {"z", angular_z}};
    mRosClient.publishToTopic("/armbot/mobile_base_controller/cmd_vel", twistMsg);
}

void RosHandling::publishGoal(const int &index) {
    QJsonObject msg;

    QJsonArray dataArray = {
        mRobotPose[0],
        mRobotPose[1],
        goalPoints[index].x,
        goalPoints[index].y,
        goalPoints[index].yaw
    };

    msg["data"] = dataArray;
    mRosClient.publishToTopic("/goal_position", msg);
}

void RosHandling::publishMoveCommand(const QString& data) {
    QJsonObject msg;
    msg["data"] = data;

    mRosClient.publishToTopic("/move_command", msg);  // Gửi JSON thay vì QString
}

void RosHandling::publishHermitePath() {
    QJsonObject msg;
    QJsonArray poses;

    for (const auto &point : hermiteCurve->getCurvePointsMeter()) {
        QJsonObject pose;
        pose["position"] = QJsonObject{{"x", point.x}, {"y", point.y}};

        QJsonObject poseStamped;
        poseStamped["header"] = QJsonObject{{"frame_id", "map"}, {"stamp", QJsonObject{{"secs", 0}, {"nsecs", 0}}}};
        poseStamped["pose"] = pose;

        poses.append(poseStamped);
    }

    QJsonObject header;
    header["frame_id"] = "map";
    header["stamp"] = QJsonObject{{"secs", 0}, {"nsecs", 0}};

    msg["header"] = header;
    msg["poses"] = poses;
    mRosClient.publishToTopic("/hermite_path", msg);
    
    QJsonObject msg_string;
    msg_string["data"] = "start";
    mRosClient.publishToTopic("/start_tracking", msg_string);
}

void RosHandling::publishVirtualWall() {
    auto virtualWallPoints = virtualWall->getVirtualWallPointsMeter();
    QJsonObject msg;
    QJsonArray poses;
    QJsonObject header;

    header["frame_id"] = "map"; 
    header["stamp"] = QJsonObject{{"secs", 0}, {"nsecs", 0}};

    if (virtualWallPoints.empty()) {
        poses = {};
        msg["header"] = header;
        msg["poses"] = poses;
        mRosClient.publishToTopic("/virtual", msg);
        return;     
    }

    if (virtualWallPoints.size() % 2 != 0) {
        return;
    }

    for (const auto &point : virtualWallPoints) {
        QJsonObject pose;
        pose["position"] = QJsonObject{{"x", point.x}, {"y", point.y}};
        poses.append(pose);
    }

    msg["header"] = header;
    msg["poses"] = poses;
    mRosClient.publishToTopic("/virtual", msg);
}

QVariantList RosHandling::getRobotPoseMeterQml() const {
    QVariantList robotPoseList;
    for (const auto &pose : mRobotPose) {
        robotPoseList.append(pose);
    }
    return robotPoseList;
}

QVariantList RosHandling::getWaypointsQml() const {
    QVariantList waypointsList;
    waypointsList.reserve(mWaypoints.size());
    for (const auto &point : mWaypoints) {
        waypointsList.append(QVariant::fromValue(QVariantList{point.first, point.second}));
    }
    return waypointsList;
}

double RosHandling::getEstimateDistanceQml() const {
    return mDistance;
}

double RosHandling::getRemainingDistanceQml() const {
    return mRemainingDistance;
}

// float ViewModel::batteryStatus() const {
//     return mBatteryStatus;
// }

QVariantList RosHandling::speedQml() const {
    QVariantList speedList;
    for (const auto &speed : mSpeed) {
        speedList.append(speed);
    }
    return speedList;
}

QVariantList RosHandling::getRobotPosePixel(const double &x, const double &y) const {
    QPair<double, double> point = hermiteCurve->getReadYaml()->convertMeterToPixel(x, y);
    return QVariantList{point.first, point.second};
}

void RosHandling::updateRosDataReceived(const QString &topic, const QJsonObject &msg) {
    if (topic == "/amcl_pose") {
        QJsonObject pose = msg["pose"].toObject()["pose"].toObject();
        double x = pose["position"].toObject()["x"].toDouble();
        double y = pose["position"].toObject()["y"].toDouble();

        QJsonObject orientation = pose["orientation"].toObject();
        double qz = orientation["z"].toDouble();
        double qw = orientation["w"].toDouble();
        
        mRobotPose[0] = std::round(x * 1000) / 1000; 
        mRobotPose[1] = std::round(y * 1000) / 1000;
        mRobotPose[2] = std::round(((2.0 * atan2(qz, qw)) * (180 / M_PI )) * 1000) / 1000;

        emit robotPoseChanged();
    } else if (topic == "/estimate_distance") {
        mDistance = msg["data"].toDouble();
        emit estimateDistanceChanged();
    } else if (topic == "/remaining_distance") {
        mRemainingDistance = msg["data"].toDouble();
        emit remainingDistanceChanged();
    } else if (topic == "/battery_status") {
        // mBatteryStatus = msg["data"].toDouble();
        // emit batteryStatusChanged();
    } else if (topic == "/result_navigation") {
        if (msg["data"].toString() == "done") {
            mWaypoints.clear();
            emit waypointsChanged();
        }
    } else if (topic == "/done_tracking") {
        if (msg["data"].toString() == "done") {
            hermiteCurve->clearCurvePoints();
        }
    } else if (topic == "/waypoints") {
        mWaypoints.clear();

        QJsonArray poses = msg["poses"].toArray();
        mWaypoints.reserve(poses.size());  

        for (const QJsonValue &pose : poses) {  
            QJsonObject position = pose.toObject()["position"].toObject();

            double x = position["x"].toDouble();
            double y = position["y"].toDouble();

            QPair<double, double> point = hermiteCurve->getReadYaml()->convertMeterToPixel(x, y);

            mWaypoints.append(point);
        }
        emit waypointsChanged();
    } else if (topic == "/armbot/mobile_base_controller/cmd_vel") {
        QJsonObject twistLinear = msg["linear"].toObject();
        QJsonObject twistAngular = msg["angular"].toObject();
        mSpeed[0] = twistLinear["x"].toDouble();
        mSpeed[1] = twistAngular["z"].toDouble();
        emit speedChanged();
    }
}

void RosHandling::clearWaypoints() {
    mWaypoints.clear();
    emit waypointsChanged();
}