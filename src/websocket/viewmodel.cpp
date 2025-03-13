#include "websocket/viewmodel.h"
#include <QtMath>
#include <QJsonArray>
#include <QDebug>

ViewModel::ViewModel(MainWindow* mainWindow, QObject *parent) : QObject(parent), mMainWindow(mainWindow) {
    connect(&mRosClient, &RosBridgeClient::receivedMessage, this, &ViewModel::updateRosData);
    mRosClient.connectToRos();

    goalPoints = {{
        {-3.0, 1.0, 90.0}, {-1.0, 1.0, 120.0}, {-4.0, 4.0, 30.0}, {-1.0, 4.0, 150.0}, {3.5, 4.0, -90.0},
        {1.0, 3.0, 0.0}, {6, 1.0, -60.0}, {-6.0, 3.5, 180.0}, {-6, 0.0, -45.0}, {-6.0, -3.0, -135.0}
    }};
}

void ViewModel::sendVelocityCommand(double linear_x, double angular_z) {
    QJsonObject twistMsg;
    twistMsg["linear"] = QJsonObject{{"x", linear_x}, {"y", 0.0}, {"z", 0.0}};
    twistMsg["angular"] = QJsonObject{{"x", 0.0}, {"y", 0.0}, {"z", angular_z}};
    mRosClient.publishToTopic("/cmd_vel", twistMsg);
}

void ViewModel::sendGoal(const int &index) {
    QJsonObject msg;

    QJsonArray dataArray = {
        mRobotPose["position_x"].toDouble(),
        mRobotPose["position_y"].toDouble(),
        goalPoints[index].x,
        goalPoints[index].y,
        goalPoints[index].z
    };

    msg["data"] = dataArray;
    mRosClient.publishToTopic("/goal_position", msg);
}

void ViewModel::sendMoveCommand(const QString& data) {
    QJsonObject msg;
    msg["data"] = data;

    mRosClient.publishToTopic("/move_command", msg);  // Gửi JSON thay vì QString
}

QVariantMap ViewModel::robotPose() const {
    return mRobotPose;
}

QVariantList ViewModel::getWaypoints() const {
    return mWaypoints;
}

float ViewModel::batteryStatus() const {
    return mBatteryStatus;
}

// QVariantList ViewModel::laserScan() const {
//     return mLaserScan;
// }

void ViewModel::updateRosData(const QString &topic, const QJsonObject &msg) {
    if (topic == "/amcl_pose") {
        QJsonObject pose = msg["pose"].toObject()["pose"].toObject();
        double x = pose["position"].toObject()["x"].toDouble();
        double y = pose["position"].toObject()["y"].toDouble();

        QJsonObject orientation = pose["orientation"].toObject();
        double qz = orientation["z"].toDouble();
        double qw = orientation["w"].toDouble();
        
        mRobotPose["position_x"] = x;
        mRobotPose["position_y"] = y;        
        mRobotPose["angular_yaw"] = 2.0 * qAtan2(qz, qw);


        emit robotPoseChanged();
    } else if (topic == "/battery_status") {
        mBatteryStatus = msg["data"].toDouble();
        emit batteryStatusChanged();
    } else if (topic == "/waypoints") {
        mWaypoints.clear();

        QJsonArray posesArray = msg["poses"].toArray();
        int size = posesArray.size();

        QVariantList xList, yList;
        xList.reserve(size);
        yList.reserve(size);

        for (const auto &poseValue : posesArray) {
            QJsonObject pose = poseValue.toObject();
            QJsonObject position = pose["position"].toObject();

            xList.append(position["x"].toDouble());
            yList.append(position["y"].toDouble());
        }

        if ((xList[0].toDouble() != mRobotPose["position_x"].toDouble()) || 
            (yList[0].toDouble() != mRobotPose["position_y"].toDouble())) {

            double xDiff = mRobotPose["position_x"].toDouble() - xList[0].toDouble();
            double yDiff = mRobotPose["position_y"].toDouble() - yList[0].toDouble();

            for (size_t i = 0; i < xList.size(); ++i) {
                xList[i] = xList[i].toDouble() + xDiff;
            }
    
            for (size_t i = 0; i < yList.size(); ++i) {
                yList[i] = yList[i].toDouble() + yDiff;
            }
        }

        QVariantMap segmentWaypoints;
        // segmentWaypoints.insert("x", xList);
        // segmentWaypoints.insert("y", yList);

        for (size_t i = 0; i < xList.size(); ++i) {
            double newX = (xList[i].toDouble() - mYamlData["origin"].toList()[0].toDouble()) / mYamlData["resolution"].toDouble();
            newX = newX * (displaySize.width / sourceSize.width);
            xList[i] = newX;
        }

        for (size_t i = 0; i < yList.size(); ++i) {
            double newY = (yList[i].toDouble() - mYamlData["origin"].toList()[1].toDouble()) / mYamlData["resolution"].toDouble();
            newY = displaySize.height - (newY * (displaySize.height / sourceSize.height));
            yList[i] = newY;
        }

        segmentWaypoints["x"] = xList;
        segmentWaypoints["y"] = yList;

        mWaypoints.append(segmentWaypoints);
        emit waypointsChanged();
    }
    // } else if (topic == "/laser_scan") {
    //     m_laserScan.clear();
    //     QJsonArray ranges = msg["ranges"].toArray();
    //     for (const auto &value : ranges)
    //         m_laserScan.append(value.toDouble());
    //     emit laserScanChanged();
    // }
}


void ViewModel::onImageLoader(const int& width, const int& height, const int& sourcesizeWidth, const int& sourcesizeHeight) {
    displaySize = {width, height};
    sourceSize = {sourcesizeWidth, sourcesizeHeight};
    mYamlData = mMainWindow->getYamlValue();
}


