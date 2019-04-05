#include "voronoicellsmodel.h"

#include <iostream>

#include "../conversion/converter.h"

namespace how {
namespace ui {

VoronoiCellsModel::VoronoiCellsModel() : voronoiCells(nullptr) {}
VoronoiCellsModel::VoronoiCellsModel(
    const std::vector<model::VoronoiCell> *const voronoiCells)
    : QAbstractListModel(), voronoiCells(voronoiCells) {}

QHash<int, QByteArray> VoronoiCellsModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Centroid] = "rollCentroid";
  roles[Points] = "rollPoints";
  roles[Envelope] = "rollEnvelope";
  return roles;
}

Qt::ItemFlags VoronoiCellsModel::flags(const QModelIndex &) const {
  return Qt::ItemIsSelectable;
}

QVariant VoronoiCellsModel::headerData(int, Qt::Orientation, int) const {
  return QVariant();
}

int VoronoiCellsModel::rowCount(const QModelIndex &) const {
  return static_cast<int>(this->voronoiCells->size());
}

QVariant VoronoiCellsModel::data(const QModelIndex &index, int role) const {
  const auto &voronoiCell =
      this->voronoiCells->operator[](static_cast<std::size_t>(index.row()));
  switch (role) {
  case Centroid:
    return convert(voronoiCell.centroid);
  case Points:
    return convert(&voronoiCell.outlinePoints);
  case Envelope:
    return convert(&voronoiCell.envelope);
  default:
    return QVariant();
  }
}
} // namespace ui
} // namespace how
