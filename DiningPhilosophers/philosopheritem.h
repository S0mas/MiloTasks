#pragma once
#include <QObject>
#include <QThread>
#include <philosopher.h>

class PhilosopherItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool eating READ isEating NOTIFY eatingChanged)
    Q_PROPERTY(int index READ getId)
    std::unique_ptr<Philosopher> philosopher;
    std::unique_ptr<QThread> thread;
public:
    PhilosopherItem(std::unique_ptr<Philosopher>&& philosopher, QObject *parent = nullptr);
    ~PhilosopherItem(){
        thread->requestInterruption();
    }
    bool isEating() const noexcept {
        return philosopher->isEating();
    }

    bool getId() const noexcept {
        return philosopher->getId();
    }

    void start() const noexcept {
        thread->start();
    }
signals:
    void eatingChanged();
    void modifyNeededResources(const std::vector<int>& resourcesIds);

public slots:
    void eatingWasChanged() {
        emit eatingChanged();
    }
};
