#pragma once
#include "philosopheritem.h"
#include "waiter.h"

#include <memory>
#include <vector>

#include <QObject>
#include <QThread>
#include <QVector>

class PhilosopherList : public QObject
{
    Q_OBJECT
    Waiter waiter;
    std::unique_ptr<QThread> waiterThread;
    int getNextIndex(const int index) const noexcept;
public:
    explicit PhilosopherList(QObject *parent = nullptr);
    ~PhilosopherList() override;
    QVector<PhilosopherItem*> items() const;
    Q_INVOKABLE void start();
signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved(const int index);
    void postItemRemoved();
public slots:
    Q_INVOKABLE void appendItem();
    Q_INVOKABLE void removeItem(const int index);
private:
    std::vector<std::unique_ptr<PhilosopherItem>> mItems;
};
