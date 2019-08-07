#include "philosopher.h"
#include "waiter.h"

#include <chrono>
#include <thread>

#include <QCoreApplication>
#include <QRandomGenerator>
#include <QThread>

void Philosopher::releaseResources() noexcept {
    for(auto const& id : handledResourcesIds)
        emit releaseResource(id);
    handledResourcesIds.clear();
}

void Philosopher::eat() {
    eating = true;
    emit eatingChanged();
    std::this_thread::sleep_for(std::chrono::seconds(QRandomGenerator::global()->generate()%3 + 1));
    releaseResources();
    eating = false;
    emit eatingChanged();
    canEat = false;
}

void Philosopher::think() {
    std::this_thread::sleep_for(std::chrono::milliseconds(QRandomGenerator::global()->generate()%100+200));
}

Philosopher::Philosopher(const std::vector<int> &neededResourceIds, Waiter *waiter) : id(idCounter++), neededResourceIds(neededResourceIds) {
    QObject::connect(this, SIGNAL(sendRequest(const Request&)), waiter, SLOT(receiveRequest(const Request&)));
    QObject::connect(this, SIGNAL(releaseResource(const int)), waiter, SLOT(resourceReleased(const int)));
    QObject::connect(this, SIGNAL(removeReservations(const int)), waiter, SLOT(reservationRemoved(const int)));
    QObject::connect(this, SIGNAL(removeRequest(const int)), waiter, SLOT(requestRemoved(const int)));
    QObject::connect(waiter, SIGNAL(grantPermission(const Permission&)), this, SLOT(permissionGranted(const Permission&)));
}

void Philosopher::permissionGranted(const Permission &permission) {
    if(permission.sender == id) {
        handledResourcesIds = permission.resourceIds;
        requestSended = false;
        canEat = true;
    }
}

void Philosopher::neededResourcesModified(const std::vector<int> &resourceIds) {
    QMutexLocker lock(&neededResourceIdsMutex);
    neededResourceIds = resourceIds;
}

void Philosopher::start() {
    while(!QThread::currentThread()->isInterruptionRequested()){
        if(canEat)
            eat();
        if(!requestSended){
            requestSended = true;
            QMutexLocker lock(&neededResourceIdsMutex);
            emit sendRequest(Request(id, neededResourceIds));
        }
        think();
        QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
    }
    releaseResources();
    if(requestSended)
        emit removeRequest(id);
    emit removeReservations(id);
    disconnect(this);
}

bool Philosopher::isEating() const noexcept {
    return eating;
}

bool Philosopher::getId() const noexcept {
    return id;
}

std::vector<int> Philosopher::getNeededResources() {
    QMutexLocker lock(&neededResourceIdsMutex);
    return neededResourceIds;
}
