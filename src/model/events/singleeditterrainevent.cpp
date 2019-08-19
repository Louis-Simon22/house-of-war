#include "singleeditterrainevent.h"

namespace how {
namespace model {

SingleEditTerrainEvent::SingleEditTerrainEvent(const types::point_t &position,
                                               TerrainType terrainType)
    : position(position), terrainType(terrainType) {}

SingleEditTerrainEvent::~SingleEditTerrainEvent() {}

void SingleEditTerrainEvent::applyEvent(EntitiesManager &entitiesManager,
                                        SelectionManager &) const {
  auto &tilesRTree = entitiesManager.getTilesRTree();
  auto tilePtr = tilesRTree.getValueByPosition(this->position);
  tilePtr->setTerrainType(this->terrainType);
}

} // namespace model
} // namespace how
