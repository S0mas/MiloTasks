#include "philosophersmodel.h"
#include "philosopherslist.h"

PhilosophersModel::PhilosophersModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{
}

int PhilosophersModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}


QVariant PhilosophersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    switch(role) {
        case EatingRole:
            return QVariant(mList->items()[index.row()]->isEating());
        case IdRole:
            return QVariant(mList->items()[index.row()]->id);
    }

    return QVariant();
}

QHash<int, QByteArray> PhilosophersModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[EatingRole] = "isEating";
    names[IdRole] = "id";
    return names;
}

PhilosophersList* PhilosophersModel::list() const {
    return mList;
}

void PhilosophersModel::setList(PhilosophersList* newList) {
    beginResetModel();
    if(mList)
        mList->disconnect(this);
    mList = newList;
    if(mList) {
        connect(mList, &PhilosophersList::philosopherRemoved, this, [=]() {
            endInsertRows();
        });
        connect(mList, &PhilosophersList::philosopherAdded, this, [=]() {
            endRemoveRows();
        });
    }
    endResetModel();
}
