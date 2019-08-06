#pragma once
#include "philosopher.h"
#include "waiter.h"
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
    void removeItem(const int index);
private:
    QVector<Philosopher*> mItems;
};


