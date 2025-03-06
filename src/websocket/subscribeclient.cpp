#include "websocket/subscribeclient.h"
#include <QJsonDocument>
#include <QDebug>

SubscribeClient::SubscribeClient(const QString &serverAddress, QObject *parent)
    : QObject(parent), mServerAddress(serverAddress) {
    // Sử dụng constructor với origin mặc định và version mặc định
    mWebSocket = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this);

    connect(mWebSocket, &QWebSocket::connected, this, &SubscribeClient::onConnected);
    connect(mWebSocket, &QWebSocket::textMessageReceived, this, &SubscribeClient::onTextMessageReceived);
    connect(mWebSocket, &QWebSocket::disconnected, this, &SubscribeClient::onDisconnected);
}

SubscribeClient::~SubscribeClient() {
    mWebSocket->close();
    delete mWebSocket;
}

void SubscribeClient::start() {
    mWebSocket->open(QUrl(mServerAddress));
}

void SubscribeClient::onConnected() {
    subscribe(); // Gọi hàm ảo để class con xử lý
}

void SubscribeClient::onTextMessageReceived(const QString &message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObj = doc.object();

    if (jsonObj.contains("topic") && jsonObj.contains("msg")) {
        QString topic = jsonObj["topic"].toString();
        processMessage(topic, jsonObj["msg"].toObject());
        emit dataChanged();
    } else {
        qDebug() << "Invalid message format:" << message;
    }
}

void SubscribeClient::onDisconnected() {
    mWebSocket->open(QUrl(mServerAddress)); // Thử kết nối lại
}