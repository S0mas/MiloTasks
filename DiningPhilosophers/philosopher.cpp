#include "philosopher.h"
#include "waiter.h"


Philosopher::Philosopher(const std::vector<int> &neededResourceIds, Waiter *waiter) : id(idCounter++), neededResourceIds(neededResourceIds) {
    qDebug() << "Philosopher created with id" << id << " needed reasourcesIds: " << neededResourceIds[0] << " " << neededResourceIds[1];
    QObject::connect(this, SIGNAL(sendRequest(const Request&)), waiter, SLOT(receiveRequest(const Request&)));
    QObject::connect(this, SIGNAL(releaseResource(const int&)), waiter, SLOT(resourceReleased(const int&)));
    QObject::connect(waiter, SIGNAL(grantPermission(const Permission&)), this, SLOT(permissionGranted(const Permission&)));
}

