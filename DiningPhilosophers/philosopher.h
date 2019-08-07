#pragma once
#include "permission.h"
#include "request.h"

#include <utility>
#include <queue>
#include <memory>

#include <atomic>
#include <QMutexLocker>
#include <thread>
#include <chrono>
#include <QDebug>
#include <QThread>
#include <QRandomGenerator>
#include <QCoreApplication>

class Waiter;
class Philosopher : public QObject {
    Q_OBJECT
    QMutex mutex;
    inline static int idCounter = 1;
    const int id;
    bool requestSended = false;
    std::atomic<bool> eating = false;
    bool canEat = false;
    std::vector<int> neededResourceIds;
    std::vector<int> handledResourcesIds;

    void releaseResources() noexcept {
        for(auto const& id : handledResourcesIds)
            emit releaseResource(id);
        handledResourcesIds.clear();
    }

    void eat() noexcept {
        eating = true;
        emit eatingChanged();
        std::this_thread::sleep_for(std::chrono::seconds(QRandomGenerator::global()->generate()%3 + 1));
        releaseResources();
        eating = false;
        emit eatingChanged();
        canEat = false;
    }

    void think() {
        std::this_thread::sleep_for(std::chrono::milliseconds(QRandomGenerator::global()->generate()%100+200));
    }
public:
    Philosopher(const std::vector<int>& neededResourceIds, Waiter* waiter);
    ~Philosopher() override {
        releaseResources();
        disconnect(this);
    }
signals:
    void eatingChanged();
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

    void neededResourcesModified(const std::vector<int>& resourceIds) noexcept {
        neededResourceIds = resourceIds;
    }

    void start() {
        while(!QThread::currentThread()->isInterruptionRequested()){
            if(canEat)
                eat();
            if(!requestSended){
                requestSended = true;
                //QMutexLocker locker(&mutex);
                emit sendRequest(Request(id, neededResourceIds));
            }
            think();
            QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
        }
    }

    //Thread Safe functions
    bool isEating() const noexcept {
        return eating;
    }

    bool getId() const noexcept {
        return id;
    }

    void modifyNeededResources(const std::vector<int>& resourceIds) noexcept {
        //QMutexLocker locker(&mutex);
        neededResourceIds = resourceIds;
    }
};


