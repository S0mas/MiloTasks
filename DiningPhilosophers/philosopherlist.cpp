#include "philosopherlist.h"

PhilosopherList::PhilosopherList(QObject *parent) : QObject(parent) {
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({0, 1}), &waiter)));
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({1, 2}), &waiter)));
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({2, 3}), &waiter)));
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({3, 4}), &waiter)));
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({4, 0}), &waiter)));

    waiterThread = std::make_unique<QThread>();
    waiter.moveToThread(waiterThread.get());
    connect(waiterThread.get(), SIGNAL(started()), &waiter, SLOT(start()));
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

void PhilosopherList::appendItem() {
    emit preItemAppended();
    emit mItems.back()->modifyNeededResources({static_cast<int>(mItems.size() - 1), static_cast<int>(mItems.size())});
    mItems.push_back(std::make_unique<PhilosopherItem>(std::make_unique<Philosopher>(std::vector<int>({static_cast<int>(mItems.size()), 0}), &waiter)));
    mItems.back()->start();
    emit postItemAppended();
}

int PhilosopherList::getNextIndex(const int index) const noexcept {
    return (index+1)%mItems.size();
}

void PhilosopherList::removeItem(const int index) {
    emit preItemRemoved(index);
    //emit mItems.at(getNextIndex(index))->modifyNeededResources({mItems.size-});
    //mItems.erase(mItems.begin() + index);
    //mItems.back()->modifyNeededResources({static_cast<int>(mItems.size() - 1), 0});
    emit postItemRemoved();
}
