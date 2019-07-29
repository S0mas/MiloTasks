#ifndef PHILOSOPHERITEM_H
#define PHILOSOPHERITEM_H

#include <QAbstractItemModel>
#include "fork.h"

class PhilosophersList;

class PhilosophersModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PhilosophersList *list READ list WRITE setList)
    std::vector<Fork> forks;
    PhilosophersList* mList;
public:
    enum {
        EatingRole = Qt::UserRole,
        IdRole
    };

    explicit PhilosophersModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    PhilosophersList* list() const;
    void setList(PhilosophersList* newList);
};

#endif // PHILOSOPHERITEM_H
