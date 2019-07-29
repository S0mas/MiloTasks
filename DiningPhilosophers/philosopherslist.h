#pragma once

#include <QObject>
#include <vector>
#include <philosopher.h>
#include <memory>

#include "fork.h"

class PhilosophersList : public QObject
{
    Q_OBJECT
    std::vector<std::unique_ptr<Philosopher>> philosophers;
    std::vector<Fork> forks;
public:
    explicit PhilosophersList(QObject *parent = nullptr);

    const std::vector<std::unique_ptr<Philosopher>>& items() const noexcept;
signals:
    void philosopherAdded();
    void philosopherRemoved();
public slots:
    void addPhilosopher();
    void removePhilosopher();
};
