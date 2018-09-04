#include "worldmodel.h"
#include <QDebug>

WorldModel::WorldModel() : QAbstractListModel()
{
}

WorldModel::WorldModel(QVector<Cell*> *points) : QAbstractListModel()
{
    this->points = unique_ptr<QVector<Cell*>*>(&points);
}

QHash<int, QByteArray> WorldModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PosX] = "posX";
    roles[PosY] = "posY";
    return roles;
}

Qt::ItemFlags WorldModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable;
}

QVariant WorldModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

int WorldModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "Size : " + (*this->points)->size();
    return (*this->points)->size();
}

QVariant WorldModel::data(const QModelIndex &index, int role) const
{
    Cell* cell = (*this->points)->at(index.row());
    switch (role) {
        case PosX:
            return cell->x();
        case PosY:
            return cell->y();
    }
    return 0;
}
