#include "rosbridgeclient.h"
#include <QDebug>

RosBridgeClient::RosBridgeClient(QObject *parent) : QObject(parent) {}

RosBridgeClient::~RosBridgeClient() {
    qDeleteAll(mStringClients);
    qDeleteAll(mPoseClients);
}

void RosBridgeClient::addStringClient(const QString &topic) {
    if (!mStringClients.contains(topic)) {
        StringSubscribeClient* client = new StringSubscribeClient(mServerAddress, topic, this);
        mStringClients[topic] = client;
        connect(client, &StringSubscribeClient::dataChanged, this, [this, topic]() {
            mTopicData[topic] = getStringData(topic);
            emit topicDataChanged();
        });
        client->start();
    }
}

void RosBridgeClient::addPoseClient(const QString &topic) {
    if (!mPoseClients.contains(topic)) {
        PoseSubscribeClient* client = new PoseSubscribeClient(mServerAddress, topic, this);
        mPoseClients[topic] = client;
        connect(client, &PoseSubscribeClient::dataChanged, this, [this, topic]() {
            mTopicData[topic] = getPoseData(topic);
            emit topicDataChanged();
        });
        client->start();
    }
}

QVariant RosBridgeClient::getStringData(const QString &topic) const {
    if (mStringClients.contains(topic)) {
        QMap<QString, QVariant> data = mStringClients[topic]->data();
        return data.value(topic, "No data");
    }
    return "No data";
}

QVariant RosBridgeClient::getPoseData(const QString &topic) const {
    if (mPoseClients.contains(topic)) {
        QMap<QString, QVariant> data = mPoseClients[topic]->data();
        return data.value(topic, QVariantMap());
    }
    return QVariantMap();
}