#include "worlddataqmlwrapper.h"

#include <boost/geometry/algorithms/covered_by.hpp>

#include "../../model/entities/movement/movementcalculator.h"
#include "../../model/modeltypes.h"
#include "../../model/world/worldgeneration/worldgenerator.h"
#include "../conversion/converter.h"

namespace how {
namespace ui {
WorldDataQMLWrapper::WorldDataQMLWrapper() : QObject(nullptr) {}

WorldDataQMLWrapper::WorldDataQMLWrapper(model::WorldData *worldDataPtr)
    : worldDataPtr(worldDataPtr) {}

bool WorldDataQMLWrapper::isPointWithinVoronoiCell(int voronoiCellIndex,
                                                   int pointX, int pointY) {
  const auto &polygon =
      this->worldDataPtr
          ->getVoronoiCellByDesc(static_cast<std::size_t>(voronoiCellIndex))
          ->polygon;
  return bg::covered_by(model::types::point_t(pointX, pointY), polygon);
}

const QRect WorldDataQMLWrapper::getWorldBounds() const {
  const auto &bounds = this->worldDataPtr->getBounds();
  return convert(bounds);
}

const model::WorldData *WorldDataQMLWrapper::getWorldDataPtr() const {
  return this->worldDataPtr;
}

const model::VoronoiCell *
WorldDataQMLWrapper::getVoronoiCellAt(int voronoiCellIndex) const {
  return this->worldDataPtr->getVoronoiCellByDesc(
      static_cast<std::size_t>(voronoiCellIndex));
}

VoronoiCellsModel *WorldDataQMLWrapper::getVoronoiCellsModel() const {
  return new VoronoiCellsModel(this->worldDataPtr);
}
} // namespace ui
} // namespace how
