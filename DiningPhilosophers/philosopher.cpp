#include "philosopher.h"
#include "waiter.h"

#include <chrono>
#include <thread>

#include <QCoreApplication>
#include <QRandomGenerator>
#include <QThread>

int Philosopher::idCounter = 1;

void Philosopher::releaseResources() noexcept {
    QMutexLocker lock(&resourceIdsMutex);
    for(auto const& id : handledResourcesIds)
        emit releaseResource(id);
    handledResourcesIds.clear();
    handledResourcesChanged();
}

void Philosopher::eat() {
    eating = true;
    emit eatingChanged();
    std::this_thread::sleep_for(std::chrono::seconds(QRandomGenerator::global()->generate()%3 + 1));
    eating = false;
    emit eatingChanged();
    releaseResources();
    canEat = false;
}

void Philosopher::think() {
    std::this_thread::sleep_for(std::chrono::milliseconds(QRandomGenerator::global()->generate()%100+200));
}

Philosopher::Philosopher(const std::vector<int> &neededResourceIds, Waiter *waiter) : id(idCounter++), neededResourceIds(neededResourceIds) {
    QObject::connect(this, &Philosopher::sendRequest, waiter, &Waiter::receiveRequest);
    QObject::connect(this, &Philosopher::releaseResource, waiter, &Waiter::resourceReleased);
    QObject::connect(this, &Philosopher::removeReservations, waiter, &Waiter::reservationRemoved);
    QObject::connect(this, &Philosopher::removeRequest, waiter, &Waiter::requestRemoved);
    QObject::connect(waiter, &Waiter::grantPermission, this, &Philosopher::permissionGranted);
}

void Philosopher::permissionGranted(const Permission &permission) {
    if(permission.sender == id) {
        QMutexLocker lock(&resourceIdsMutex);
        handledResourcesIds = permission.resourceIds;
        handledResourcesChanged();
        requestSended = false;
        canEat = true;
    }
}

void Philosopher::neededResourcesModified(const std::vector<int> &resourceIds) {
    QMutexLocker lock(&resourceIdsMutex);
    neededResourceIds = resourceIds;
    emit neededResourcesChanged();
}

void Philosopher::start() {
    while(!QThread::currentThread()->isInterruptionRequested()){
        if(canEat)
            eat();
        if(!requestSended){
            requestSended = true;
            QMutexLocker lock(&resourceIdsMutex);
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

int Philosopher::getId() const noexcept {
    return id;
}

std::vector<int> Philosopher::getNeededResources() {
    QMutexLocker lock(&resourceIdsMutex);
    return neededResourceIds;
}

std::vector<int> Philosopher::getHandledResources() {
    QMutexLocker lock(&resourceIdsMutex);
    return handledResourcesIds;
}
