#include "websocket/publishclient.h"
#include <QJsonDocument>
#include <QDebug>

PublishClient::PublishClient(const QString &serverAddress, QObject *parent)
    : QObject(parent), mServerAddress(serverAddress) {
    // Sử dụng constructor với origin mặc định và version mặc định
    mWebSocket = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this);

    connect(mWebSocket, &QWebSocket::connected, this, &PublishClient::onConnected);
    connect(mWebSocket, &QWebSocket::disconnected, this, &PublishClient::onDisconnected);
}

PublishClient::~PublishClient() {
    mWebSocket->close();
    delete mWebSocket;
}

void PublishClient::start() {
    mWebSocket->open(QUrl(mServerAddress));
}

void PublishClient::publish(const QVariant &message) {
    if (mWebSocket->state() == QAbstractSocket::ConnectedState) {
        QString formattedMsg = formatMessage(message);
        mWebSocket->sendTextMessage(formattedMsg);
        qDebug() << "Published message:" << formattedMsg;
    } else {
        qDebug() << "WebSocket not connected, cannot publish";
    }
}

void PublishClient::onConnected() {
    qDebug() << "Publish WebSocket connected to:" << mServerAddress;
}

void PublishClient::onDisconnected() {
    qDebug() << "Publish WebSocket disconnected";
    mWebSocket->open(QUrl(mServerAddress)); // Thử kết nối lại
}