#ifndef STRINGSUBSCRIBECLIENT_H
#define STRINGSUBSCRIBECLIENT_H

#include "websocket/subscribeclient.h"

class StringSubscribeClient : public SubscribeClient {
    Q_OBJECT

public:
    explicit StringSubscribeClient(const QString &serverAddress, const QString &topic, QObject *parent = nullptr);

protected:
    void subscribe() override;
    void processMessage(const QString &topic, const QJsonObject &msgObj) override;

private:
    QString mTopic;
};

#endif // STRINGSUBSCRIBECLIENT_H