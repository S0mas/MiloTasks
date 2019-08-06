#include "philosophersmodel.h"

PhilosopherList *PhilosophersModel::list() const {
    return philosopherList;
}

void PhilosophersModel::setList(PhilosopherList *list) {
    beginResetModel();
    if(philosopherList)
        philosopherList->disconnect(this);
    philosopherList = list;

    if(philosopherList){
        connect(philosopherList, &PhilosopherList::preItemAppended, this, [=]() {
            const auto index = philosopherList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });

        connect(philosopherList, &PhilosopherList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(philosopherList, &PhilosopherList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(philosopherList, &PhilosopherList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }
    endResetModel();
}

int PhilosophersModel::rowCount(const QModelIndex& parent) const {
    if(parent.isValid() || !philosopherList)
        return 0;
    return philosopherList->items().size();
}

QVariant PhilosophersModel::data(const QModelIndex& index, int role) const {
    int i = index.row();
    if (!philosopherList || i < 0 || i >= philosopherList->items().size())
        return QVariant(QVariant::Invalid);

    return QVariant::fromValue(philosopherList->items().at(i));
}
