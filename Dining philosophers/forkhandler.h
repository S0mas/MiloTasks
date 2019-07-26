#pragma once

#include "fork.h"
#include <queue>
#include <QObject>

class Request {
public:
    const unsigned senderId;
    const unsigned requestedForkId;
    Request(const unsigned philosopherId, const unsigned requestedForkId) : senderId(philosopherId), requestedForkId(requestedForkId) {}
};

class Msg {
public:
    const unsigned receiverId;
    Fork* fork;
    Msg(const unsigned philosopherId, Fork* fork) : receiverId(philosopherId), fork(fork) {}
};

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
