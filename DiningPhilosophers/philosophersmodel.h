#pragma once
#include "philosopherlist.h"

#include <QAbstractListModel>

class PhilosophersModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PhilosopherList* list READ list WRITE setList)
    PhilosopherList* philosopherList;
public:
    explicit PhilosophersModel();
    PhilosopherList* list() const;
    void setList(PhilosopherList* list);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};



