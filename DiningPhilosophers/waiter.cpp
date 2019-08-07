#include "waiter.h"

#include <QCoreApplication>
#include <QThread>

bool Waiter::isReservationPossible(const Request &request) {
    for(auto const& id : request.resourceIds)
        if(resourcesReservation[id] != 0)//already reserved ->> philosophers ids starts from 1
            return false;
    return true;
}

bool Waiter::areResourcesReservedBySomeoneElse(const Request &request) {
    for(auto const& id : request.resourceIds)
        if(resourcesReservation[id] != 0 && resourcesReservation[id] != request.sender)
            return true;
    return false;
}

void Waiter::removeReservation(const std::vector<Waiter::ResourceId> &resourceIds) {
    for(auto const& id : resourceIds)
        resourcesReservation[id] = 0;
}

void Waiter::addReservation(const Request &request) {
    for(auto const& id : request.resourceIds)
        resourcesReservation[id] = request.sender;
}

bool Waiter::areResourcesAvailable(const Request &request) {
    bool resourceBlocked = false;
    for(auto const& id : request.resourceIds)
        if(resourceStates[id] == BLOCKED) {
            resourceBlocked = true;
            break;
        }

    if(resourceBlocked && isReservationPossible(request))
        addReservation(request);
    else if(!resourceBlocked && !areResourcesReservedBySomeoneElse(request)){
        removeReservation(request.resourceIds);
        return true;
    }
    return false;
}

void Waiter::markResourcesBlocked(const std::vector<Waiter::ResourceId> &resourceIds) {
    for(auto const& id : resourceIds)
        resourceStates[id] = BLOCKED;
}

void Waiter::releaseResource(const int resourceId) {
    resourceStates[resourceId] = FREE;
}

bool Waiter::handleRequest(const Request &request) {
    if(areResourcesAvailable(request)){
        emit grantPermission(Permission(request.sender, request.resourceIds));
        markResourcesBlocked(request.resourceIds);
        return true;
    }
    return false;
}

void Waiter::handleRequests() {
    for (auto it = requests.begin(); it != requests.end(); ) {
        if(handleRequest(*it)){
            it = requests.erase(it);
        }
        else
            ++it;
    }
}

int Waiter::getNewResource() noexcept {
    static int r;
    return r++;
}

void Waiter::receiveRequest(const Request &request) {
    requests.push_back(request);
}

void Waiter::resourceReleased(const int &resourceId) {
    releaseResource(resourceId);
}

void Waiter::reservationRemoved(const int &philosopherId) {
    for(auto& reservation : resourcesReservation)
        if(reservation.second == philosopherId)
            reservation.second = 0;
}

void Waiter::requestRemoved(const int &philosopherId) {
    for (auto it = requests.begin(); it != requests.end(); ) {
        if(it->sender == philosopherId){
            requests.erase(it);
            return;
        }
        else
            ++it;
    }
}

void Waiter::start() {
    while(!QThread::currentThread()->isInterruptionRequested()){
        handleRequests();
        QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
    }
}
