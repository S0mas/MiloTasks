#pragma once
#include <utility>
#include <queue>
#include <memory>
#include "forkhandler.h"
#include <thread>
#include <chrono>
#include <QThread>
#include <QDebug>
#include <QVector>

class Philosopher : public QThread {
    inline static unsigned idCounter;
    const unsigned id;
    std::vector<ForkHandler*> forkHandlers;

public:
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
        qDebug() << "EATING... id:" << id;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        for(auto& forkHandler : forkHandlers)
           forkHandler->getFork()->use();
    }

    void think() {
        qDebug() << "THINKING... id:" << id;
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

    void run() override {
        qDebug() << "STARTED... id:" << id;
        while(true)
            proceed();
    }
};
