#include "philosopherlist.h"

PhilosopherList::PhilosopherList(QObject *parent) : QObject(parent) {
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({Waiter::getNewResource(), Waiter::getNewResource()}), &waiter)));
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({1, Waiter::getNewResource()}), &waiter)));
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({2, Waiter::getNewResource()}), &waiter)));
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({3, Waiter::getNewResource()}), &waiter)));
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({4, 0}), &waiter)));

    waiterThread = std::make_unique<QThread>();
    waiter.moveToThread(waiterThread.get());
    connect(waiterThread.get(), SIGNAL(started()), &waiter, SLOT(start()));
}

PhilosopherList::~PhilosopherList() {
    disconnect(this);
    waiterThread->requestInterruption();
    waiterThread->quit();
    waiterThread->wait();
}

QVector<PhilosopherItem*> PhilosopherList::items() const {
    QVector<PhilosopherItem*> result;
    for(const auto& element : mItems)
        result.append(element.get());
    return result;
}

void PhilosopherList::start() {
    waiterThread->start();
    for(auto const& item : mItems)
        item->start();

}

static int getCommonResource(const std::vector<int>& lhs, const std::vector<int>& rhs){
    int common = -1;
    for(auto const& resourceId : lhs)
            for(auto const& resourceId2 : rhs)
                if(resourceId == resourceId2)
                    common = resourceId;
    return common;
}

void PhilosopherList::appendItem() {
    emit preItemAppended();
    std::vector<int> resourcesOfNewPhilosopher;
    if(mItems.size() > 1){
        auto first = mItems[0]->getNeededResources();
        auto last = mItems.back()->getNeededResources();
        int commonResource = getCommonResource(first, last);
        int newResourceId = Waiter::getNewResource();
        resourcesOfNewPhilosopher = {commonResource, newResourceId};
        for(auto& resourceId : last)
            if(resourceId == commonResource)
                resourceId = newResourceId;
        emit mItems.back()->modifyNeededResources(last);

    }
    else if(mItems.size() == 1){
        resourcesOfNewPhilosopher = mItems[0]->getNeededResources();
    }
    else
        resourcesOfNewPhilosopher = {Waiter::getNewResource(), Waiter::getNewResource()};
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(resourcesOfNewPhilosopher, &waiter)));
    mItems.back()->start();
    emit postItemAppended();
}

int PhilosopherList::getNextIndex(const int index) const noexcept {
    return (index+1)%mItems.size();
}

static std::vector<int> getModifiedResources(const std::vector<int>& lhs, const std::vector<int>& rhs) {
    std::vector<int> modifedResources;
    int resourceIdToIgnore = getCommonResource(lhs, rhs);
    for(auto const& resourceId : lhs)
        if(resourceId != resourceIdToIgnore)
            modifedResources.push_back(resourceId);
    for(auto const& resourceId : rhs)
        if(resourceId != resourceIdToIgnore)
            modifedResources.push_back(resourceId);
    return modifedResources;
}

void PhilosopherList::removeItem(const int index) {
    emit preItemRemoved(index);
    if(mItems.size() != 1) {
        auto lhs = mItems.at(index)->getNeededResources();
        auto rhs = mItems.at(getNextIndex(index))->getNeededResources();
        emit mItems.at(getNextIndex(index))->modifyNeededResources(getModifiedResources(lhs,rhs));
    }
    mItems.erase(mItems.begin() + index);
    emit postItemRemoved();
}
