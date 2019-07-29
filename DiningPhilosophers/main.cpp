#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "philosophersmodel.h"
#include "philosopherslist.h"
#include <vector>
#include <iostream>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<PhilosophersModel>("Philosophers.model", 1, 0, "PhilosophersModel");
    qmlRegisterUncreatableType<PhilosophersList>("Philosopher", 1, 0, "List", QStringLiteral("PhilosophersList should not be created in QML"));
    PhilosophersList philosophersList;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("philosophersList"), &philosophersList);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    //for(auto& philosopher : philosophers)
    //    philosopher.start();
    return app.exec();
}
