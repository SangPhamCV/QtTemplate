#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QVariantMap>
#include <QVariantList>
#include <iostream>
#include <array>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtMath>
#include <QDebug>
#include "rosbridgeclient.h"
#include "mainwindow.h"

class ViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantMap robotPose READ robotPose NOTIFY robotPoseChanged)
    Q_PROPERTY(float batteryStatus READ batteryStatus NOTIFY batteryStatusChanged)
    Q_PROPERTY(QVariantList waypointsQml READ getWaypoints NOTIFY waypointsChanged)
    // Q_PROPERTY(QVariantList laserScan READ laserScan NOTIFY laserScanChanged)

public:
    explicit ViewModel(MainWindow *mainWindow, QObject *parent = nullptr);

    Q_INVOKABLE void sendVelocityCommand(double linear_x, double angular_z);
    Q_INVOKABLE void sendGoal(const int &index);
    Q_INVOKABLE void sendMoveCommand(const QString &data);
    Q_INVOKABLE QVariantList getWaypoints() const;

    QVariantMap robotPose() const;
    float batteryStatus() const;
    // QVariantList laserScan() const;

signals:
    void robotPoseChanged();
    void batteryStatusChanged();
    void waypointsChanged();
    // void laserScanChanged();

public slots:
    void onImageLoader(const int& width, const int& height, const int& sourcesizeWidth, const int& sourcesizeHeight);

private slots:
    void updateRosData(const QString &topic, const QJsonObject &msg);

private:
    struct ImageSize {
        int width, height;
    };

    struct GoalPoint {
        double x, y, z;
    };

    std::array<GoalPoint, 10> goalPoints;
    ImageSize displaySize;
    ImageSize sourceSize;

    MainWindow* mMainWindow;
    QVariantMap mYamlData;
    RosBridgeClient mRosClient;
    QVariantMap mRobotPose;
    QVariantList mWaypoints;
    float mBatteryStatus = 0.0;
    // QVariantList mLaserScan;
};

#endif // VIEWMODEL_H
