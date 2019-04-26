#include "voronoicellsmodel.h"

#include "../conversion/converter.h"

namespace how {
namespace ui {

VoronoiCellsModel::VoronoiCellsModel() : EntityModel(), WorldManagerPtr(nullptr) {}

VoronoiCellsModel::VoronoiCellsModel(const model::WorldManager *WorldManagerPtr)
    : EntityModel(), WorldManagerPtr(WorldManagerPtr) {
  for (std::size_t i = 0; i < WorldManagerPtr->getVoronoiCellCount(); i++) {
    this->uuidToIndexMap[WorldManagerPtr->getVoronoiCellByDesc(i).getUuid()] =
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
  return static_cast<int>(WorldManagerPtr->getVoronoiCellCount());
}

QVariant VoronoiCellsModel::data(const QModelIndex &index, int role) const {
  const auto &voronoiCell =
      WorldManagerPtr->getVoronoiCellByDesc(static_cast<std::size_t>(index.row()));
  switch (role) {
  case Envelope:
    return convert(voronoiCell.getEnvelope());
  default:
    return QVariant();
  }
}
} // namespace ui
} // namespace how
