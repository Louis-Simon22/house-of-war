#include "cellsmodel.h"
#include <iostream>

namespace how {
namespace ui {

CellsModel::CellsModel() : points(nullptr) {}
CellsModel::CellsModel(const std::vector<point_t> *const points)
    : QAbstractListModel(), points(points) {}

QHash<int, QByteArray> CellsModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[PosX] = "posX";
  roles[PosY] = "posY";
  return roles;
}

Qt::ItemFlags CellsModel::flags(const QModelIndex &) const {
  return Qt::ItemIsSelectable;
}

QVariant CellsModel::headerData(int, Qt::Orientation, int) const {
  return QVariant();
}

int CellsModel::rowCount(const QModelIndex &) const {
  return static_cast<int>(this->points->size());
}

QVariant CellsModel::data(const QModelIndex &index, int role) const {
  const auto &point = this->points->operator[](static_cast<std::size_t>(index.row()));
  switch (role) {
  case PosX:
    return bg::get<0>(point);
  case PosY:
    return bg::get<1>(point);
  default:
    return 0;
  }
}
} // namespace ui
} // namespace how
