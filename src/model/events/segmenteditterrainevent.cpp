#include "segmenteditterrainevent.h"

namespace how {
namespace model {

SegmentEditTerrainEvent::SegmentEditTerrainEvent(
    const types::segment_t &segment, TerrainType terrainType)
    : ModelEvent(), segment(segment), terrainType(terrainType) {}

SegmentEditTerrainEvent::~SegmentEditTerrainEvent() {}

void SegmentEditTerrainEvent::applyEvent(EntitiesManager &entitiesManager,
                                         SelectionManager &) const {
  auto &tilesRTree = entitiesManager.getTilesRTree();
  auto tilePtrs = tilesRTree.getValuesBySegmentIntersection(this->segment);
  for (auto &tilePtr : tilePtrs) {
    tilePtr->setTerrainType(this->terrainType);
  }
}

} // namespace model
} // namespace how
