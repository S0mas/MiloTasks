#pragma once
#include "philosopher.h"
#include "waiter.h"
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QQmlListProperty>
#include <QList>

class PhilosophersModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Philosopher> list READ list)
    Waiter waiter;
public:
    PhilosophersModel() {
        m_list.append(new Philosopher({4, 0}));
        m_list.append(new Philosopher({0, 1}));
        m_list.append(new Philosopher({1, 2}));
        m_list.append(new Philosopher({2, 3}));
        m_list.append(new Philosopher({3, 4}));

        for(auto resourceId = 0; resourceId < m_list.size(); ++resourceId)
            waiter.registerResource(resourceId);
        for(auto philosopher : m_list){
            QObject::connect(philosopher, SIGNAL(sendRequest(const Request&)), &waiter, SLOT(receiveRequest(const Request&)));
            QObject::connect(philosopher, SIGNAL(releaseResource(const int&)), &waiter, SLOT(resourceReleased(const int&)));
            QObject::connect(&waiter, SIGNAL(grantPermission(const int&)), philosopher, SLOT(permissionGranted(const int&)));
        }
    }

    void start() {
        waiter.start();
        for(auto& philosopher : m_list)
            qobject_cast<Philosopher*>(philosopher)->start();
    }

    QQmlListProperty<Philosopher> list();
    void append(Philosopher*);
    int count() const;
    Philosopher* philosopher(int) const;
    void clear();

private:
    inline static void append(QQmlListProperty<Philosopher>*, Philosopher*);
    inline static int count(QQmlListProperty<Philosopher>*);
    inline static Philosopher* philosopher(QQmlListProperty<Philosopher>*, int);
    inline static void clear(QQmlListProperty<Philosopher>*);

    QList<Philosopher*> m_list;

signals:
    void listChanged();
};

