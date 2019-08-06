#pragma once
#include "request.h"
#include <list>
#include <map>
#include <QThread>
#include <QCoreApplication>

class Waiter : public QThread {
    Q_OBJECT
    enum RessourceState {
        FREE,
        BLOCKED
    };
    std::list<Request> requests;
    std::map<int, bool> resourceStates;

    bool areResourcesAvailable(const std::vector<int>& resourceIds) noexcept {
        for(auto const& id : resourceIds)
            if(resourceStates[id] == BLOCKED)
                return false;
        return true;
    }

    void markResourcesBlocked(const std::vector<int>& resourceIds) noexcept {
        for(auto const& id : resourceIds)
            resourceStates[id] = BLOCKED;
    }

    void releaseResource(const int resourceId) noexcept {
        resourceStates[resourceId] = FREE;
    }

    bool handleRequest(const Request& request) noexcept {
        if(areResourcesAvailable(request.resourceIds)){
            emit grantPermission(request.sender);
            markResourcesBlocked(request.resourceIds);
            return true;
        }
        return false;
    }

    void handleRequests() noexcept {
        for (auto it = requests.begin(); it != requests.end(); ) {
            if(handleRequest(*it))
                it = requests.erase(it);
            else
                ++it;
        }
    }
public:
    Waiter(){}

    void run() override {
        while(true){
            handleRequests();
            QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, 100);
        }
    }

    void registerResource(const int id) noexcept {
        resourceStates[id] = FREE;
    }
signals:
    void grantPermission(const int& id);

public slots:
    void receiveRequest(const Request& request) noexcept {
        requests.push_back(request);
    }

    void resourceReleased(const int& resourceId) noexcept {
        releaseResource(resourceId);
    }
};
