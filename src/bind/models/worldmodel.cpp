#include "worldmodel.h"
#include <iostream>

namespace how {
namespace bind {
namespace models {

WorldModel::WorldModel() : points(nullptr), vd(nullptr) {}
WorldModel::WorldModel(const std::vector<point_t> *points, const vd_t *vd)
    : QAbstractListModel(), points(points), vd(vd) {}

QHash<int, QByteArray> WorldModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[PosX] = "posX";
  roles[PosY] = "posY";
  return roles;
}

Qt::ItemFlags WorldModel::flags(const QModelIndex &) const {
  return Qt::ItemIsSelectable;
}

QVariant WorldModel::headerData(int, Qt::Orientation, int) const {
  return QVariant();
}

int WorldModel::rowCount(const QModelIndex &) const {
  return this->points->size();
}

QVariant WorldModel::data(const QModelIndex &index, int role) const {
  const auto &point = this->points->at(index.row());
  switch (role) {
  case PosX:
    return bg::get<0>(point);
  case PosY:
    return bg::get<1>(point);
  default:
    return 0;
  }
}
} // namespace models
} // namespace bind
} // namespace how
