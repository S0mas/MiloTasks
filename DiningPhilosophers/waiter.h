#pragma once
#include "permission.h"
#include "request.h"

#include <list>
#include <map>

#include <QObject>

class Waiter : public QObject {
    Q_OBJECT
    enum RessourceState {
        FREE,
        BLOCKED,
    };
    using OwnerId = int;
    using ResourceId = int;
    std::list<Request> requests;
    std::map<ResourceId, OwnerId> resourcesReservation;//0 means it is not reserved;
    std::map<ResourceId, RessourceState> resourceStates;

    bool isReservationPossible(const Request& request);
    bool areResourcesReservedBySomeoneElse(const Request& request);
    void removeReservation(const std::vector<ResourceId>& resourceIds);
    void addReservation(const Request& request);
    bool areResourcesAvailable(const Request& request);
    void markResourcesBlocked(const std::vector<ResourceId>& resourceIds);
    void releaseResource(const int resourceId);
    bool handleRequest(const Request& request);
    void handleRequests();
public:
    static int getNewResource() noexcept;
    Waiter() = default;
signals:
    void grantPermission(const Permission& permission);
public slots:
    void receiveRequest(const Request& request);
    void resourceReleased(const int& resourceId);
    void reservationRemoved(const int& philosopherId);
    void requestRemoved(const int& philosopherId);
    void start();
};
