#ifndef POSESUBSCRIBECLIENT_H
#define POSESUBSCRIBECLIENT_H

#include "websocket/subscribeclient.h"

class PoseSubscribeClient : public SubscribeClient {
    Q_OBJECT

public:
    explicit PoseSubscribeClient(const QString &serverAddress, const QString &topic, QObject *parent = nullptr);

protected:
    void subscribe() override;
    void processMessage(const QString &topic, const QJsonObject &msgObj) override;

private:
    QString mTopic;
};

#endif // POSESUBSCRIBECLIENT_H