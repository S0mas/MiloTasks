#include "philosopherlist.h"

PhilosopherList::PhilosopherList(QObject *parent) : QObject(parent) {
    mItems.emplace_back(std::make_unique<Philosopher>(std::vector<int>({0, 1}), &waiter));
    mItems.emplace_back(std::make_unique<Philosopher>(std::vector<int>({1, 2}), &waiter));
    mItems.emplace_back(std::make_unique<Philosopher>(std::vector<int>({2, 3}), &waiter));
    mItems.emplace_back(std::make_unique<Philosopher>(std::vector<int>({3, 4}), &waiter));
    mItems.emplace_back(std::make_unique<Philosopher>(std::vector<int>({4, 0}), &waiter));

    for(auto resourceId = 0; resourceId < mItems.size(); ++resourceId)
        waiter.registerResource(resourceId);
}

QVector<Philosopher*> PhilosopherList::items() const {
    QVector<Philosopher*> result;
    for(auto& element : mItems)
        result.append(element.get());
    return result;
}

void PhilosopherList::start() {
    waiter.start();
    for(auto& philosopher : mItems)
        philosopher->start();

}

void PhilosopherList::appendItem() {
    emit preItemAppended();
    mItems.back()->modifyNeededResources({static_cast<int>(mItems.size() - 1), static_cast<int>(mItems.size())});
    waiter.registerResource(static_cast<int>(mItems.size()));
    auto philosopher = std::make_unique<Philosopher>(std::vector<int>({static_cast<int>(mItems.size()), 0}), &waiter);
    philosopher->start();
    mItems.push_back(std::move(philosopher));
    emit postItemAppended();
}

void PhilosopherList::removeItem() {
    emit preItemRemoved(mItems.size() - 1);
    //unregisterResource TODO::: check if this is needed (registration)
    mItems.erase(mItems.begin() + mItems.size() - 1);
    mItems.back()->modifyNeededResources({static_cast<int>(mItems.size() - 1), 0});
    emit postItemRemoved();
}
