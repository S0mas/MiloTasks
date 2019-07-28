#pragma once
#include <utility>
#include <queue>
#include <memory>
#include "forkhandler.h"
#include <thread>
#include <chrono>
#include <QThread>
#include <QDebug>

class Philosopher : public QThread {
    static unsigned idCounter;
    const unsigned id;
    ForkHandler leftForkHandler;
    ForkHandler rightForkHandler;
public:
    Philosopher(const unsigned leftForkId, const unsigned rightForkId) : id(idCounter++), leftForkHandler(leftForkId, id), rightForkHandler(rightForkId, id) {}

    void sendRequests() {
        if(leftForkHandler.isEmpty())
            leftForkHandler.sendRequest();
        if(rightForkHandler.isEmpty())
            rightForkHandler.sendRequest();
    }

    void handleRequests() {
        if(leftForkHandler.isAvailable() && !leftForkHandler.isForkClean())
            leftForkHandler.handleRequest();
        if(rightForkHandler.isAvailable() && !rightForkHandler.isForkClean())
            rightForkHandler.handleRequest();
    }

    void eat() {
        qDebug() << "3.";
        std::this_thread::sleep_for(std::chrono::seconds(5));
        leftForkHandler.useFork();
        rightForkHandler.useFork();

    }

    void think() {
        qDebug() << "2.";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    void proceed() {
        if(leftForkHandler.isAvailable() && leftForkHandler.isForkClean() && rightForkHandler.isAvailable() && rightForkHandler.isForkClean())
            eat();
        else {
           sendRequests();
           think();
           handleRequests();
        }
    }

    ForkHandler& getLeftForkHandler() noexcept {
        return leftForkHandler;
    }

    ForkHandler& getRightForkHandler() noexcept {
        return rightForkHandler;
    }

    void run() override {
        qDebug() << "1.";
        while(true)
            proceed();
    }
};
