#include "philosopherslist.h"
#include <QDebug>

PhilosophersList::PhilosophersList(QObject *parent) : QObject(parent) {
    for(auto i = 0u; i < 5; ++i)
        philosophers.emplace_back(new Philosopher);
    forks.resize(5);
    philosophers[0]->giveForks(&forks[0], &forks[4]);
    philosophers[0]->connectForkHandlers(philosophers[1].get(), philosophers[4].get());
    for(auto i = 1u; i < forks.size()-1; ++i)
        philosophers[i]->giveForks(&forks[i], nullptr);
    for(int i = 0; i < philosophers.size(); ++i) {
        auto const& left = (i + 1) < philosophers.size() ? i + 1 : 0;
        auto const& right = (i - 1) >= 0 ? i - 1 : philosophers.size() - 1;
        philosophers[i]->connectForkHandlers(philosophers[left].get(), philosophers[right].get());
    }
}

const std::vector<std::unique_ptr<Philosopher>>& PhilosophersList::items() const noexcept {
    return philosophers;
}

void PhilosophersList::addPhilosopher() {
    philosophers.emplace_back();
    emit philosopherAdded();
}

void PhilosophersList::removePhilosopher() {
    philosophers.pop_back();
    emit philosopherRemoved();
}
