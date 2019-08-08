#pragma once
#include <philosopher.h>

#include <QObject>
#include <QThread>

class PhilosopherItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool eating READ isEating NOTIFY eatingChanged)
    Q_PROPERTY(int index READ getId NOTIFY indexChange)
    Q_PROPERTY(std::vector<int> neededResources READ getNeededResources NOTIFY neededResourcesChanged)
    Q_PROPERTY(std::vector<int> handledResources READ getHandledResources NOTIFY handledResourcesChanged)
    std::unique_ptr<Philosopher> philosopher;
    std::unique_ptr<QThread> thread;
public:
    PhilosopherItem(std::unique_ptr<Philosopher>&& philosopher, QObject *parent = nullptr);
    ~PhilosopherItem();
    bool isEating() const noexcept;
    int getId() const noexcept;
    std::vector<int> getNeededResources() const;
    std::vector<int> getHandledResources() const;
    void start() const;
signals:
    void eatingChanged();
    void indexChange();
    void neededResourcesChanged();
    void handledResourcesChanged();
    void modifyNeededResources(const std::vector<int>& resourcesIds);
public slots:
    void eatingWasChanged();
    void neededResourcesWasChanged();
    void handledResourcesWasChanged();
};
