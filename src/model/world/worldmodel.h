#ifndef MAP_H
#define MAP_H

#include <QVector2D>
#include <memory>
#include "cell.h"
#include <QVariant>
#include <QAbstractListModel>

using namespace std;

class WorldModel : public QAbstractListModel
{
    Q_OBJECT
public:
    WorldModel();
    WorldModel(QVector<Cell*>* points);
    enum CellRoles {
        PosX = Qt::UserRole + 1,
        PosY
    };

    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex&) const override;
    QVariant headerData(int, Qt::Orientation, int) const override;
    int rowCount(const QModelIndex&) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    unique_ptr<QVector<Cell*>> points;

};

#endif
