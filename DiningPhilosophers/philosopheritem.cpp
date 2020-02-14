#include "philosopheritem.h"
#include <memory>

PhilosopherItem::PhilosopherItem(std::unique_ptr<Philosopher>&& philosopher, QObject *parent) : QObject(parent), philosopher(std::move(philosopher)) {
    connect(this->philosopher.get(), &Philosopher::eatingChanged, this, &PhilosopherItem::eatingWasChanged);
    connect(this->philosopher.get(), &Philosopher::neededResourcesChanged, this, &PhilosopherItem::neededResourcesWasChanged);
    connect(this->philosopher.get(), &Philosopher::handledResourcesChanged, this, &PhilosopherItem::handledResourcesWasChanged);
    connect(this, &PhilosopherItem::modifyNeededResources, this->philosopher.get(), &Philosopher::neededResourcesModified);

    thread = std::make_unique<QThread>();
    this->philosopher->moveToThread(thread.get());
    connect(thread.get(), &QThread::started, this->philosopher.get(), &Philosopher::start);
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

std::vector<int> PhilosopherItem::getHandledResources() const {
    if(philosopher)
        return philosopher->getHandledResources();
    return {};
}

void PhilosopherItem::start() const {
    thread->start();
}

void PhilosopherItem::eatingWasChanged() {
    emit eatingChanged();
}

void PhilosopherItem::neededResourcesWasChanged() {
    emit neededResourcesChanged();
}

void PhilosopherItem::handledResourcesWasChanged() {
    emit handledResourcesChanged();
}
