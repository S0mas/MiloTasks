#pragma once

#include <QObject>
#include "fork.h"

class ForkHandler : public QObject {
    Q_OBJECT
    bool requestSended;
    bool requestReceived;
    Fork* fork = nullptr;
public:
    ForkHandler() : requestSended(false) {}

    bool isEmpty() const noexcept {
        return fork == nullptr;
    }

    bool isAvailable() const noexcept {
        return !isEmpty();
    }

    Fork* getFork() noexcept {
        return fork;
    }

    void sendRequest() noexcept {
        if(!requestSended) {
            requestSended = true;
            emit sendReq();
        }
    }

    void handleRequest() noexcept {
        if(requestReceived){
            fork->clean();
            emit sendFork(fork);
            fork = nullptr;
            requestReceived = false;
        }
    }

    void connectForkHandler(ForkHandler* forkHandler) const noexcept {
        connect(this, SIGNAL(sendReq()), forkHandler, SLOT(receiveRequest()));
        connect(this, SIGNAL(sendFork(Fork*)), forkHandler, SLOT(receiveFork(Fork*)));
        connect(forkHandler, SIGNAL(sendReq()), this, SLOT(receiveRequest()));
        connect(forkHandler, SIGNAL(sendFork(Fork*)), this, SLOT(receiveFork(Fork*)));
    }
signals:
    void sendReq();
    void sendFork(Fork*);

public slots:
    void receiveRequest() {
        requestReceived = true;
    }

    void receiveFork(Fork* receivedFork) {
        fork = receivedFork;
        requestSended = false;
    }
};
