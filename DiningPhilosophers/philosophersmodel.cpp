#include "philosophersmodel.h"


QQmlListProperty<Philosopher> PhilosophersModel::list() {
    return QQmlListProperty<Philosopher>(this, this,
                                         &PhilosophersModel::append,
                                         &PhilosophersModel::count,
                                         &PhilosophersModel::philosopher,
                                         &PhilosophersModel::clear);
}

void PhilosophersModel::append(Philosopher *)
{

}

int PhilosophersModel::count() const
{

}

Philosopher *PhilosophersModel::philosopher(int) const
{

}

void PhilosophersModel::clear()
{

}
