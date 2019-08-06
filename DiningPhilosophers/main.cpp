#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "philosophersmodel.h"
#include <vector>
#include <iostream>
#include <QDebug>
#include "waiter.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qRegisterMetaType<Request>();
    qmlRegisterType<PhilosophersModel>();
    qmlRegisterType<Philosopher>();

    PhilosophersModel model;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("modelFull", &model);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    model.start();
    return app.exec();
}
