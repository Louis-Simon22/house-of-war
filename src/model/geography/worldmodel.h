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

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    unique_ptr<QVector<Cell*>*> points;

};

#endif
