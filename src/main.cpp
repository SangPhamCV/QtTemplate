#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "loginhandler.h"
#include "readyaml.h"
#include "filehandler.h"
#include "hermitecurve.h"
#include "roshandling.h"
#include "virtualwall.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    LoginHandler loginHandler;
    ReadYaml readYaml;
    FileHandler fileHandler;
    HermiteCurve hermiteCurve(nullptr, &readYaml);
    VirtualWall virtualWall(nullptr, &readYaml);

    RosHandling rosHandling(&hermiteCurve, &virtualWall, nullptr);

    engine.rootContext()->setContextProperty("loginHandlerQML", &loginHandler);
    engine.rootContext()->setContextProperty("readYamlQML", &readYaml);
    engine.rootContext()->setContextProperty("hermiteCurveQML", &hermiteCurve);
    engine.rootContext()->setContextProperty("fileHandlerQML", &fileHandler);
    engine.rootContext()->setContextProperty("rosHandlingQML", &rosHandling);
    engine.rootContext()->setContextProperty("virtualWallQML", &virtualWall);

    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}