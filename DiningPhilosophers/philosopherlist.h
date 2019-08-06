#pragma once
#include "philosopher.h"
#include "waiter.h"
#include <memory>
#include <vector>
#include <QObject>

class PhilosopherList : public QObject
{
    Q_OBJECT
    Waiter waiter;
public:
    explicit PhilosopherList(QObject *parent = nullptr);

    QVector<Philosopher*> items() const;
    Q_INVOKABLE void start();
signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved(const int index);
    void postItemRemoved();

public slots:
    Q_INVOKABLE void appendItem();
    void removeItem();
private:
    std::vector<std::unique_ptr<Philosopher>> mItems;
};


