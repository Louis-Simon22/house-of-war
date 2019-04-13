#include "voronoicellsmodel.h"

#include <iostream>

#include "../conversion/converter.h"

namespace how {
namespace ui {

VoronoiCellsModel::VoronoiCellsModel() : EntityModel(), worldDataPtr(nullptr) {}
VoronoiCellsModel::VoronoiCellsModel(const model::WorldData *worldDataPtr)
    : EntityModel(), worldDataPtr(worldDataPtr) {
  for (std::size_t i = 0; i < worldDataPtr->getVoronoiCellCount(); i++) {
    this->uuidToIndexMap[worldDataPtr->getVoronoiCellByDesc(i)->uuid] =
        this->index(static_cast<int>(i));
  }
}

QHash<int, QByteArray> VoronoiCellsModel::roleNames() const {
  QHash<int, QByteArray> roles;
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
  return static_cast<int>(worldDataPtr->getVoronoiCellCount());
}

QVariant VoronoiCellsModel::data(const QModelIndex &index, int role) const {
  const auto &voronoiCell =
      worldDataPtr->getVoronoiCellByDesc(static_cast<std::size_t>(index.row()));
  switch (role) {
  case Envelope:
    return convert(voronoiCell->envelope);
  default:
    return QVariant();
  }
}
} // namespace ui
} // namespace how
