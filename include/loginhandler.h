#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include <QObject>

class LoginHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)

public:
    explicit LoginHandler(QObject *parent = nullptr);

    Q_INVOKABLE bool login(const QString &username, const QString &password);  // Make this method accessible in QML

    QString statusMessage() const;

signals:
    void statusMessageChanged();
    void loggedIn(bool);  // Signal for login result

private:
    QString mStatusMessage;
};

#endif // LOGINHANDLER_H

