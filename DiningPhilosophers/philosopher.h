#pragma once
#include <utility>
#include <queue>
#include <memory>
#include "forkhandler.h"
#include <thread>
#include <chrono>
#include <QThread>
#include <QDebug>
#include <QObject>

class Philosopher : public QThread {
    Q_OBJECT
    inline static unsigned idCounter;
    std::vector<ForkHandler*> forkHandlers;
    bool eating = false;
public:
    const unsigned id;
    Philosopher() : id(idCounter++) {
        forkHandlers.push_back(new ForkHandler());
        forkHandlers.push_back(new ForkHandler());
    }

    void sendRequests() {
        for(auto& forkHandler : forkHandlers){
            if(forkHandler->isEmpty())
                forkHandler->sendRequest();
        }
    }

    void handleRequests() {
        for(auto& forkHandler : forkHandlers){
            if(forkHandler->isAvailable() && forkHandler->getFork()->isDirty())
                forkHandler->handleRequest();
        }
    }

    void eat() {
        emit startEating();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        for(auto& forkHandler : forkHandlers)
           forkHandler->getFork()->use();
        emit stopEating();
    }

    void think() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void proceed() {
        bool canEat = true;
        for(auto& forkHandler : forkHandlers){
            if(!forkHandler->isAvailable() || forkHandler->getFork()->isDirty()){
                canEat = false;
                break;
            }
        }
        if(canEat)
            eat();
        else {
           sendRequests();
           think();
           handleRequests();
        }
    }

    void giveForks(Fork* left, Fork* right) noexcept {
        forkHandlers[0]->receiveFork(left);
        forkHandlers[1]->receiveFork(right);
    }

    void connectForkHandlers(Philosopher* onTheLeft, Philosopher* onTheRight) const noexcept {
        forkHandlers[0]->connectForkHandler(onTheLeft->forkHandlers[1]);
        forkHandlers[1]->connectForkHandler(onTheRight->forkHandlers[0]);
    }

    bool isEating() const noexcept {
        return eating;
    }

    void run() override {
        qDebug() << "STARTED... id:" << id;
        while(true)
            proceed();
    }

signals:
    void startEating();
    void stopEating();
};
