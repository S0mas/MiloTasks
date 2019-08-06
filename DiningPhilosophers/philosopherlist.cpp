#include "philosopherlist.h"

PhilosopherList::PhilosopherList(QObject *parent) : QObject(parent) {
    mItems.append(new Philosopher({0, 1}));
    mItems.append(new Philosopher({1, 2}));
    mItems.append(new Philosopher({2, 3}));
    mItems.append(new Philosopher({3, 4}));
    mItems.append(new Philosopher({4, 0}));

    for(auto resourceId = 0; resourceId < mItems.size(); ++resourceId)
        waiter.registerResource(resourceId);
    for(auto philosopher : mItems) {
        QObject::connect(philosopher, SIGNAL(sendRequest(const Request&)), &waiter, SLOT(receiveRequest(const Request&)));
        QObject::connect(philosopher, SIGNAL(releaseResource(const int&)), &waiter, SLOT(resourceReleased(const int&)));
        QObject::connect(&waiter, SIGNAL(grantPermission(const Permission&)), philosopher, SLOT(permissionGranted(const Permission&)));
    }
}

QVector<Philosopher*> PhilosopherList::items() const {
    return mItems;
}

void PhilosopherList::start() {
    waiter.start();
    for(auto& philosopher : mItems)
        philosopher->start();

}

void PhilosopherList::appendItem() {
    emit preItemAppended();
    auto philosopher = new Philosopher({mItems.size(), 0});
    mItems.back()->modifyNeededResources({mItems.size() - 1, mItems.size()});
    mItems.append(philosopher);
    waiter.registerResource(mItems.size());
    QObject::connect(philosopher, SIGNAL(sendRequest(const Request&)), &waiter, SLOT(receiveRequest(const Request&)));
    QObject::connect(philosopher, SIGNAL(releaseResource(const int&)), &waiter, SLOT(resourceReleased(const int&)));
    QObject::connect(&waiter, SIGNAL(grantPermission(const Permission&)), philosopher, SLOT(permissionGranted(const Permission&)));
    philosopher->start();
    emit postItemAppended();
}

void PhilosopherList::removeItem(const int index) {
    emit preItemRemoved(index);
    mItems.removeAt(index);
    emit postItemRemoved();
}
