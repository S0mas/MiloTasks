#include "philosopheritem.h"

PhilosopherItem::PhilosopherItem(std::unique_ptr<Philosopher>&& philosopher, QObject *parent) : QObject(parent), philosopher(std::move(philosopher)) {
    connect(this->philosopher.get(), SIGNAL(eatingChanged()), this, SLOT(eatingWasChanged()));
    connect(this, SIGNAL(modifyNeededResources(const std::vector<int>&)), this->philosopher.get(), SLOT(neededResourcesModified(const std::vector<int>&)));

    thread = std::make_unique<QThread>();
    this->philosopher->moveToThread(thread.get());
    connect(thread.get(), SIGNAL(started()), this->philosopher.get(), SLOT(start()));
}

PhilosopherItem::~PhilosopherItem(){
    disconnect(this);
    thread->requestInterruption();
    thread->quit();
    thread->wait();
}

bool PhilosopherItem::isEating() const noexcept {
    if(philosopher)
        return philosopher->isEating();
    return false;
}

int PhilosopherItem::getId() const noexcept {
    if(philosopher)
        return philosopher->getId();
    return 0;
}

std::vector<int> PhilosopherItem::getNeededResources() const {
    if(philosopher)
        return philosopher->getNeededResources();
    return {};
}

void PhilosopherItem::start() const {
    thread->start();
}

void PhilosopherItem::eatingWasChanged() {
    emit eatingChanged();
}
