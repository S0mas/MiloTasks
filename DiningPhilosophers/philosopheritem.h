#pragma once
#include <philosopher.h>

#include <QObject>
#include <QThread>

class PhilosopherItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool eating READ isEating NOTIFY eatingChanged)
    Q_PROPERTY(int index READ getId)
    std::unique_ptr<Philosopher> philosopher;
    std::unique_ptr<QThread> thread;
public:
    PhilosopherItem(std::unique_ptr<Philosopher>&& philosopher, QObject *parent = nullptr);
    ~PhilosopherItem();
    bool isEating() const noexcept;
    int getId() const noexcept;
    std::vector<int> getNeededResources() const;
    void start() const;
signals:
    void eatingChanged();
    void modifyNeededResources(const std::vector<int>& resourcesIds);
public slots:
    void eatingWasChanged();
};
