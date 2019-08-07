#pragma once
#include "permission.h"
#include "request.h"
#include <list>
#include <map>
#include <QObject>
#include <QDebug>
#include <QCoreApplication>

class Waiter : public QObject {
    Q_OBJECT

    enum RessourceState {
        FREE,
        BLOCKED,
    };
    using OwnerId = int;//0 means it is not reserved;
    using ResourceId = int;//0 means it is not reserved;
    std::list<Request> requests;
    std::map<ResourceId, OwnerId> resourcesReservation;
    std::map<ResourceId, RessourceState> resourceStates;

    bool isReservationPossible(const Request& request) noexcept {
        for(auto const& id : request.resourceIds)
            if(resourcesReservation[id] != 0)//already reserved ->> philosophers ids starts from 1
                return false;
        return true;
    }

    bool areResourcesReservedBySomeoneElse(const Request& request) {
        for(auto const& id : request.resourceIds)
            if(resourcesReservation[id] != 0 && resourcesReservation[id] != request.sender)
                return true;
        return false;
    }

    void removeReservation(const std::vector<ResourceId>& resourceIds) noexcept {
        for(auto const& id : resourceIds)
            resourcesReservation[id] = 0;
    }

    void addReservation(const Request& request) {
        for(auto const& id : request.resourceIds)
            resourcesReservation[id] = request.sender;
    }

    bool areResourcesAvailable(const Request& request) noexcept {
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
        else {

        }
        return false;
    }

    void markResourcesBlocked(const std::vector<ResourceId>& resourceIds) noexcept {
        for(auto const& id : resourceIds)
            resourceStates[id] = BLOCKED;
    }

    void releaseResource(const int resourceId) noexcept {
        resourceStates[resourceId] = FREE;
    }

    bool handleRequest(const Request& request) noexcept {
        if(areResourcesAvailable(request)){
            emit grantPermission(Permission(request.sender, request.resourceIds));
            markResourcesBlocked(request.resourceIds);
            return true;
        }

        return false;

    }

    void handleRequests() noexcept {
        for (auto it = requests.begin(); it != requests.end(); ) {
            if(handleRequest(*it)){
                it = requests.erase(it);
            }
            else
                ++it;
        }
    }
public:
    Waiter(){}
signals:
    void grantPermission(const Permission& permission);

public slots:
    void receiveRequest(const Request& request) noexcept {
        requests.push_back(request);
        qDebug() << "Request received" << request.sender;
    }

    void resourceReleased(const int& resourceId) noexcept {
        releaseResource(resourceId);
    }

    void start() {
        while(true){
            handleRequests();
            QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
        }
    }
};
