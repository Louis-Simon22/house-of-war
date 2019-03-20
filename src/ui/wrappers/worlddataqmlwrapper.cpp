#include "worlddataqmlwrapper.h"

#include "../../model/entities/movement/movementcalculator.h"
#include "../../model/world/worldgeneration/worldgenerator.h"

namespace how {
namespace ui {
WorldDataQMLWrapper::WorldDataQMLWrapper() : QObject(nullptr) {}

WorldDataQMLWrapper::WorldDataQMLWrapper(WorldData *worldDataPtr)
    : worldDataPtr(worldDataPtr) {}

CellsModel *WorldDataQMLWrapper::getCellsModel() const {
  return new CellsModel(this->worldDataPtr->getCellCentroids());
}

const QList<QVariant> WorldDataQMLWrapper::getOutlineSegments() const {
  return convert(this->worldDataPtr->getUniqueVoronoiSegments());
}

const QList<QVariant> WorldDataQMLWrapper::getPathSegments() const {
  return convert(this->worldDataPtr->getUniqueDelaunaySegments());
}

const QRect WorldDataQMLWrapper::getWorldBounds() const {
  const auto *bounds = this->worldDataPtr->getBounds();
  return QRect(
      bg::get<bg::min_corner, 0>(bounds), bg::get<bg::min_corner, 1>(bounds),
      bg::get<bg::max_corner, 0>(bounds), bg::get<bg::max_corner, 1>(bounds));
}

const QList<QVariant> WorldDataQMLWrapper::convert(
    const std::vector<model::types::segment_t> *segments) {
  auto convertedSegments = QList<QVariant>();

  for (auto outlineSegment : *segments) {
    const auto &p1 =
        QPoint(bg::get<0, 0>(outlineSegment), bg::get<0, 1>(outlineSegment));
    const auto &p2 =
        QPoint(bg::get<1, 0>(outlineSegment), bg::get<1, 1>(outlineSegment));
    convertedSegments.insert(convertedSegments.size(),
                             QList<QVariant>({p1, p2}));
  }

  return convertedSegments;
}
} // namespace ui
} // namespace how
