#pragma once
#include "permission.h"
#include "request.h"

#include <atomic>

#include <QMutexLocker>
#include <QObject>

class Waiter;
class Philosopher : public QObject {
    Q_OBJECT
    inline static int idCounter = 1;
    const int id;
    QMutex neededResourceIdsMutex;
    std::atomic<bool> eating = false;
    std::vector<int> neededResourceIds;
    std::vector<int> handledResourcesIds;
    bool requestSended = false;
    bool canEat = false;

    void releaseResources() noexcept;
    void eat();
    void think();
public:
    Philosopher(const std::vector<int>& neededResourceIds, Waiter* waiter);
    ~Philosopher() override {}
signals:
    void eatingChanged();
    void sendRequest(const Request& request);
    void releaseResource(const int id);
    void removeReservations(const int);
    void removeRequest(const int);
    void neededResources(const int);
public slots:
    void permissionGranted(const Permission& permission);
    void neededResourcesModified(const std::vector<int>& resourceIds);
    void start();

    //Thread Safe functions
    bool isEating() const noexcept;
    bool getId() const noexcept;
    std::vector<int> getNeededResources();
};
