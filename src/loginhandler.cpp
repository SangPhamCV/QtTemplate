#include "loginhandler.h"

LoginHandler::LoginHandler(QObject *parent) : QObject(parent), mStatusMessage("") {}

bool LoginHandler::login(const QString &username, const QString &password) {
    if (username.isEmpty() || password.isEmpty()) {
        mStatusMessage = "Username or Password cannot be empty";
        emit statusMessageChanged();
        emit loggedIn(false);  // Emit false when login fails
        return false;
    }

    if (username == "sang" && password == "1") {
        mStatusMessage = "";
        emit statusMessageChanged();
        emit loggedIn(true);  // Emit true when login is successful
        return true;
    }

    mStatusMessage = "Incorrect username or password";
    emit statusMessageChanged();
    emit loggedIn(false);  // Emit false when login fails
    return false;
}

QString LoginHandler::statusMessage() const {
    return mStatusMessage;
}
