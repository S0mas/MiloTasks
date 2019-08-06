#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "philosophersmodel.h"
#include <vector>
#include <iostream>
#include <QDebug>
#include <QQmlComponent>
#include "waiter.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qRegisterMetaType<Request>();
    qRegisterMetaType<Permission>();
    qmlRegisterType<Philosopher>();
    qmlRegisterType<PhilosophersModel>("Philosophers", 1, 0, "PhilosophersModel");
    qmlRegisterType<PhilosopherList>("Philosophers", 1, 0, "PhilosopherList");

    QQmlApplicationEngine engine;
    PhilosopherList philosopherList;
    engine.rootContext()->setContextProperty(QStringLiteral("philosopherList"), &philosopherList);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
