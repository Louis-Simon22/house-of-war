#include "edgesmodel.h"
#include <iostream>

namespace how {
namespace bind {
namespace models {

EdgesModel::EdgesModel() : vd(nullptr) {}
EdgesModel::EdgesModel(const vd_t *vd) : QAbstractListModel(), vd(vd) {}

QHash<int, QByteArray> EdgesModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[PosX1] = "posX1";
  roles[PosY1] = "posY1";
  roles[PosX2] = "posX2";
  roles[PosY2] = "posY2";
  return roles;
}

Qt::ItemFlags EdgesModel::flags(const QModelIndex &) const {
  return Qt::ItemIsSelectable;
}

QVariant EdgesModel::headerData(int, Qt::Orientation, int) const {
  return QVariant();
}

int EdgesModel::rowCount(const QModelIndex &) const {
  return this->vd->num_vertices();
}

QVariant EdgesModel::data(const QModelIndex &index, int role) const {
  //  const auto &edge = this->vd->edges()[index.row()];
  //  if (edge.is_finite() && edge.vertex0() && edge.vertex1()) {
  //    switch (role) {
  //    case PosX1:
  //      if (edge.vertex0()) {
  //        return edge.vertex0()->x();
  //      } else {
  //        return -10;
  //      }
  //    case PosY1:
  //      if (edge.vertex0()) {
  //        return edge.vertex0()->y();
  //      } else {
  //        return -10;
  //      }
  //    case PosX2:
  //      if (edge.vertex1()) {
  //        return edge.vertex1()->x();
  //      } else {
  //        return -10;
  //      }
  //    case PosY2:
  //      if (edge.vertex1()) {
  //        return edge.vertex1()->y();
  //      } else {
  //        return -10;
  //      }
  //    default:
  //      return 0;
  //    }
  //  } else {
  //    return -10;
  //  }
  const auto &vertex = this->vd->vertices()[index.row()];
  switch (role) {
  case PosX1:
  case PosX2:
    return vertex.x();
  case PosY1:
  case PosY2:
    return vertex.y();
  default:
    return -50;
  }
}
} // namespace models
} // namespace bind
} // namespace how
