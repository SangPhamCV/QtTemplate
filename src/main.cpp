#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "loginhandler.h"
#include "mainwindow.h"
#include "hermitecurve.h"
#include "rosbridgeclient.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    LoginHandler loginHandler;
    MainWindow mainWindow;
    HermiteCurve hermiteCurve;
    FileListModel fileListModel;
    RosBridgeClient* rosClient = new RosBridgeClient();

    // qmlRegisterType<LoginHandler>("myapp.loginhandler", 1, 0, "LoginHandler");

    rosClient->addStringClient("/string1");
    rosClient->addStringClient("/string2");
    rosClient->addPoseClient("/amcl_pose");

    engine.rootContext()->setContextProperty("loginHandlerQML", &loginHandler);
    engine.rootContext()->setContextProperty("mainWindowQML", &mainWindow);
    engine.rootContext()->setContextProperty("hermiteCurveQML", &hermiteCurve);
    engine.rootContext()->setContextProperty("fileListModelQML", &fileListModel);
    engine.rootContext()->setContextProperty("rosBridgeClientQML", rosClient);    

    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
