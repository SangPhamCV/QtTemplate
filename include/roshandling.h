#ifndef ROSHANDLING_H
#define ROSHANDLING_H

#include <QJsonArray>
#include "rosbridgeclient.h"
#include "hermitecurve.h"
#include "virtualwall.h"

struct Point {
    double x, y, yaw;
};

struct RobotPose {
    std::array<double, 3> meter = {0.0, 0.0, 0.0};
    std::array<double, 2> pixel = {0.0, 0.0};
};

class RosHandling : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList robotPoseMeterQml READ getRobotPoseMeterQml NOTIFY robotPoseChanged)
    // Q_PROPERTY(float batteryStatus READ batteryStatus NOTIFY batteryStatusChanged)
    Q_PROPERTY(QVariantList waypointsQml READ getWaypointsQml NOTIFY waypointsChanged)
    Q_PROPERTY(QVariantList speedQml READ speedQml NOTIFY speedChanged)
    Q_PROPERTY(double estimateDistanceQml READ getEstimateDistanceQml NOTIFY estimateDistanceChanged)
    Q_PROPERTY(double remainingDistanceQml READ getRemainingDistanceQml NOTIFY remainingDistanceChanged)

private:
    RosBridgeClient mRosClient;
    HermiteCurve* hermiteCurve;
    VirtualWall* virtualWall;

    std::array<Point, 10> goalPoints;

    QVariantMap mYamlData;
    std::array<double, 3> mRobotPose;
    std::array<double, 2> mSpeed;

    QVector<QPair<double, double>> mWaypoints;
    // float mBatteryStatus = 0.0;
    double mDistance = 0.0;
    double mRemainingDistance = 0.0;

public:
    explicit RosHandling(HermiteCurve* hermiteCurve, VirtualWall* virtualWall, QObject *parent = nullptr);

    Q_INVOKABLE void publishVelocityCommand(double linear_x, double angular_z);
    Q_INVOKABLE void publishGoal(const int &index);
    Q_INVOKABLE void publishMoveCommand(const QString &data);
    Q_INVOKABLE void publishHermitePath();
    Q_INVOKABLE void publishVirtualWall();

    Q_INVOKABLE QVariantList getRobotPosePixel(const double &x, const double &y) const;
    Q_INVOKABLE void clearWaypoints();

    QVariantList speedQml() const;
    QVariantList getWaypointsQml() const;
    QVariantList getRobotPoseMeterQml() const;
    double getEstimateDistanceQml() const;
    double getRemainingDistanceQml() const;
    // float batteryStatus() const;

signals:
    void robotPoseChanged();
    void waypointsChanged();
    void speedChanged();
    void batteryStatusChanged();
    void estimateDistanceChanged();
    void remainingDistanceChanged();

private slots:
    void updateRosDataReceived(const QString &topic, const QJsonObject &msg);
};

#endif // ROSHANDLING_H
