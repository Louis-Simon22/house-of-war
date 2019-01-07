#include "worldmodel.h"
#include <iostream>

namespace how {
namespace bind {
namespace models {

WorldModel::WorldModel() : points(nullptr) {}
WorldModel::WorldModel(const std::vector<point_t>* points)
    : QAbstractListModel(), points(points) {}

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
      return point.get<0>();
    case PosY:
      return point.get<1>();
    default:
      return 0;
  }
}
}  // namespace models
}  // namespace bind
}  // namespace how
