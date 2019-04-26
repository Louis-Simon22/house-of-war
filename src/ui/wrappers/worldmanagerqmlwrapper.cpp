#include "worldmanagerqmlwrapper.h"

#include "../../model/operations/polygonindexoperations.h"
#include "../conversion/converter.h"

namespace how {
namespace ui {
WorldManagerQMLWrapper::WorldManagerQMLWrapper() : QObject(nullptr) {}

WorldManagerQMLWrapper::WorldManagerQMLWrapper(model::WorldManager *worldManagerPtr)
    : worldManagerPtr(worldManagerPtr) {}

int WorldManagerQMLWrapper::cellIndexAtPosition(int pointX, int pointY) {
  return static_cast<int>(model::cellDescAtPosition(
      this->worldManagerPtr->getGraph(), this->worldManagerPtr->getPolygonIndexTree(),
      types::point_t(pointX, pointY)));
}

const QRect WorldManagerQMLWrapper::getWorldBounds() const {
  return convert(this->worldManagerPtr->getBounds());
}

const model::WorldManager *WorldManagerQMLWrapper::getWorldManagerPtr() const {
  return this->worldManagerPtr;
}

const model::VoronoiCell &
WorldManagerQMLWrapper::getVoronoiCellAt(int voronoiCellIndex) const {
  return this->worldManagerPtr->getVoronoiCellByDesc(
      static_cast<std::size_t>(voronoiCellIndex));
}

VoronoiCellsModel *WorldManagerQMLWrapper::getVoronoiCellsModel() const {
  return new VoronoiCellsModel(this->worldManagerPtr);
}
} // namespace ui
} // namespace how
