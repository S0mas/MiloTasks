#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "philosopher.h"
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    std::vector<Philosopher> philosophers(5);
    std::vector<Fork> forks(5);

    philosophers[0].giveForks(&forks[0], &forks[4]);
    philosophers[0].connectForkHandlers(&philosophers[1], &philosophers[4]);
    for(auto i = 1u; i < forks.size()-1; ++i)
        philosophers[i].giveForks(&forks[i], nullptr);

    for(int i = 0; i < philosophers.size(); ++i) {
        auto const& left = (i + 1) < philosophers.size() ? i + 1 : 0;
        auto const& right = (i - 1) >= 0 ? i - 1 : philosophers.size() - 1;
        std::cout << left << " " << right << std::endl;
        philosophers[i].connectForkHandlers(&philosophers[left], &philosophers[right]);
    }

    for(auto& philosopher : philosophers)
        philosopher.start();
    return app.exec();
}
