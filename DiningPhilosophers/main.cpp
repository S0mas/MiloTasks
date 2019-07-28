#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "philosopher.h"
#include <vector>

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
    philosophers[0].getLeftForkHandler().setFork(&forks[0]);
    philosophers[0].getRightForkHandler().setFork(&forks[4]);
    philosophers[1].getLeftForkHandler().setFork(&forks[1]);
    philosophers[2].getLeftForkHandler().setFork(&forks[2]);
    philosophers[3].getLeftForkHandler().setFork(&forks[3]);

    QObject::connect(&philosophers[0]
            .getLeftForkHandler(), SIGNAL(sendReq(const Request)), &philosophers[1]
            .getRightForkHandler(), SLOT(receiveRequest(const Request)));
    QObject::connect(&philosophers[0]
            .getLeftForkHandler(), SIGNAL(sendMsg(const Msg)), &philosophers[1]
            .getRightForkHandler(), SLOT(receiveFork(const Msg)));
    QObject::connect(&philosophers[1]
            .getLeftForkHandler(), SIGNAL(sendReq(const Request)), &philosophers[2]
            .getRightForkHandler(), SLOT(receiveRequest(const Request)));
    QObject::connect(&philosophers[1]
            .getLeftForkHandler(), SIGNAL(sendMsg(const Msg)), &philosophers[2]
            .getRightForkHandler(), SLOT(receiveFork(const Msg)));
    QObject::connect(&philosophers[2]
            .getLeftForkHandler(), SIGNAL(sendReq(const Request)), &philosophers[3]
            .getRightForkHandler(), SLOT(receiveRequest(const Request)));
    QObject::connect(&philosophers[2]
            .getLeftForkHandler(), SIGNAL(sendMsg(const Msg)), &philosophers[3]
            .getRightForkHandler(), SLOT(receiveFork(const Msg)));
    QObject::connect(&philosophers[3]
            .getLeftForkHandler(), SIGNAL(sendReq(const Request)), &philosophers[4]
            .getRightForkHandler(), SLOT(receiveRequest(const Request)));
    QObject::connect(&philosophers[3]
            .getLeftForkHandler(), SIGNAL(sendMsg(const Msg)), &philosophers[4]
            .getRightForkHandler(), SLOT(receiveFork(const Msg)));
    QObject::connect(&philosophers[4]
            .getLeftForkHandler(), SIGNAL(sendReq(const Request)), &philosophers[0]
            .getRightForkHandler(), SLOT(receiveRequest(const Request)));
    QObject::connect(&philosophers[4]
            .getLeftForkHandler(), SIGNAL(sendMsg(const Msg)), &philosophers[0]
            .getRightForkHandler(), SLOT(receiveFork(const Msg)));

    for(auto& philosoph : philosophers)
        philosoph.run();
    return app.exec();
}
