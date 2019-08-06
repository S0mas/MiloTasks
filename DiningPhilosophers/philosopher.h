#pragma once
#include "permission.h"
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

class Waiter;
class Philosopher : public QThread {
    Q_OBJECT
    inline static int idCounter = 1;
    int id;
    bool requestSended = false;
    bool eats = false;
    bool canEat = false;
    std::vector<int> neededResourceIds;
    std::vector<int> handledResourcesIds;

    void releaseResources() noexcept {
        for(auto const& id : handledResourcesIds)
            emit releaseResource(id);
        handledResourcesIds.clear();
    }

    void eat() noexcept {
        eats = true;
        emit eatingChanged();
        std::this_thread::sleep_for(std::chrono::seconds(QRandomGenerator::global()->generate()%3 + 1));
        releaseResources();
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
    Philosopher(const std::vector<int>& neededResourceIds, Waiter* waiter);
    ~Philosopher() override {
        releaseResources();
        disconnect(this);
        quit();
        #if QT_VERSION >= QT_VERSION_CHECK(5,2,0)
        requestInterruption();
        #endif
        qDebug() << "ddd";
        wait();
    }

    void modifyNeededResources(const std::vector<int>& resourceIds) noexcept {
        neededResourceIds = resourceIds;
        qDebug() << "Resources changed to" << neededResourceIds[0] << neededResourceIds[1];
    }

    void run() override {
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
    void permissionGranted(const Permission& permission) noexcept {
        if(permission.sender == id) {
            handledResourcesIds = permission.resourceIds;
            requestSended = false;
            canEat = true;
        }
    }
};
