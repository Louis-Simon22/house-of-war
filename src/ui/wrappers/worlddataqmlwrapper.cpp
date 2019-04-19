#include "worlddataqmlwrapper.h"

#include "../../model/entities/movement/movementcalculator.h"
#include "../../model/world/polygonindexoperations.h"
#include "../../model/world/worldgeneration/worldgenerator.h"
#include "../conversion/converter.h"

namespace how {
namespace ui {
WorldDataQMLWrapper::WorldDataQMLWrapper() : QObject(nullptr) {}

WorldDataQMLWrapper::WorldDataQMLWrapper(model::WorldData *worldDataPtr)
    : worldDataPtr(worldDataPtr) {}

int WorldDataQMLWrapper::cellDescAtPosition(int pointX, int pointY) {
  return static_cast<int>(
      model::cellDescAtPosition(this->worldDataPtr->getPolygonIndexTree(),
                                types::point_t(pointX, pointY)));
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
