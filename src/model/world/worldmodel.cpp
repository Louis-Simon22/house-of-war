#include "worldmodel.h"
#include <QDebug>

WorldModel::WorldModel() : QAbstractListModel()
{
}

WorldModel::WorldModel(QVector<Cell*> *points) : QAbstractListModel()
{
    this->points = unique_ptr<QVector<Cell*>>(points);
}

QHash<int, QByteArray> WorldModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PosX] = "posX";
    roles[PosY] = "posY";
    return roles;
}

Qt::ItemFlags WorldModel::flags(const QModelIndex&) const
{
    return Qt::ItemIsSelectable;
}

QVariant WorldModel::headerData(int, Qt::Orientation, int) const
{
    return QVariant();
}

int WorldModel::rowCount(const QModelIndex&) const
{
    return this->points->size();
}

QVariant WorldModel::data(const QModelIndex &index, int role) const
{
    Cell* cell = this->points->at(index.row());
    switch (role) {
        case PosX:
            qDebug() << "PosX: " << cell->getPosX();
            return cell->getPosX();
        case PosY:
            qDebug() << "PosY: " << cell->getPosY();
            return cell->getPosY();
        default:
            return 0;
    }
}
