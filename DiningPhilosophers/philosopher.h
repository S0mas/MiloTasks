#pragma once
#include "request.h"

#include <utility>
#include <queue>
#include <memory>

#include <thread>
#include <chrono>
#include <QThread>
#include <QDebug>
#include <QObject>
#include <QRandomGenerator>
#include <QCoreApplication>

class Philosopher : public QThread {
    Q_OBJECT
    inline static int idCounter;
    int id;
    bool requestSended = false;
    bool eats = false;
    bool canEat = false;
    std::vector<int> neededResourceIds;

    void eat() noexcept {
        eats = true;
        emit eatingChanged();
        std::this_thread::sleep_for(std::chrono::seconds(QRandomGenerator::global()->generate()%5 + 1));
        for(auto const& id : neededResourceIds)
            emit releaseResource(id);
        eats = false;
        emit eatingChanged();
        canEat = false;
    }

    void think() {
        std::this_thread::sleep_for(std::chrono::milliseconds(QRandomGenerator::global()->generate()%100+200));
    }
public:
    Q_PROPERTY(bool eating MEMBER eats NOTIFY eatingChanged)
    Q_PROPERTY(int index MEMBER id NOTIFY indexChanged)

    Philosopher(const std::vector<int>& neededResourceIds) : id(idCounter++), neededResourceIds(neededResourceIds) {}

    void run() {
        while(true){
            if(canEat)
                eat();
            if(!requestSended){
                requestSended = true;
                emit sendRequest(Request(id, neededResourceIds));
            }
            think();
            QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
        }
    }

signals:
    void eatingChanged();
    void indexChanged();
    void sendRequest(const Request& request);
    void releaseResource(const int& id) const;
public slots:
    void permissionGranted(const int& sender) noexcept {
        if(sender == id) {
            requestSended = false;
            canEat = true;
        }
    }
};
