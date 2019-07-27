#pragma once

#include "msg.h"
#include "request.h"
#include <QObject>
#include <queue>

class ForkHandler : public QObject {
    Q_OBJECT
    const unsigned forkId;
    const unsigned philosopherId;
    bool requestSended;
    Fork* fork;
    std::queue<Request> requests;
    void sendFork(const unsigned receiverId) {
       emit sendMsg(Msg(receiverId, fork));
       fork = nullptr;
    }
public:
    ForkHandler(const unsigned forkId,  const unsigned philosopherId) : forkId(forkId), philosopherId(philosopherId), requestSended(false) {}

    bool isEmpty() const noexcept {
        return fork == nullptr;
    }

    bool isAvailable() const noexcept {
        return !isEmpty();
    }

    bool isForkClean() const noexcept {
        return fork->isClean();
    }

    void useFork() const noexcept {
        fork->use();
    }

    void sendRequest() {
        if(!requestSended) {
            requestSended = true;
            emit sendReq(Request(philosopherId, forkId));
        }
    }

    void handleRequest() {
        if(requests.empty())
            return;
        const auto req = requests.front();
        fork->clean();
        sendFork(req.senderId);
        requests.pop();
    }
signals:
    void sendReq(const Request);
    void sendMsg(const Msg);

public slots:
    void receiveRequest(const Request request) {
       requests.push(request);
    }

    void receiveFork(Fork* receivedFork) {
        requestSended = false;
        fork = receivedFork;
    }
};
