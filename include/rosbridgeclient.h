#ifndef ROSBRIDGECLIENT_H
#define ROSBRIDGECLIENT_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include "websocket/stringsubscribeclient.h"
#include "websocket/posesubscribeclient.h"

class RosBridgeClient : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantMap topicData READ getTopicData NOTIFY topicDataChanged)

public:
    explicit RosBridgeClient(QObject *parent = nullptr);
    ~RosBridgeClient();

    void addStringClient(const QString &topic);
    void addPoseClient(const QString &topic);

    QVariantMap getTopicData() const { return mTopicData; }

signals:
    void topicDataChanged();

private slots:
    QVariant getStringData(const QString &topic) const;
    QVariant getPoseData(const QString &topic) const;

private:
    QMap<QString, StringSubscribeClient*> mStringClients;
    QMap<QString, PoseSubscribeClient*> mPoseClients;
    QVariantMap mTopicData; // Lưu trữ dữ liệu của tất cả topic
    const QString mServerAddress = "ws://192.168.62.138:9090";
};

#endif // ROSBRIDGECLIENT_H