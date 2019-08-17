#include "editterrainevent.h"

namespace how {
namespace model {

SingleEditTerrainEvent::SingleEditTerrainEvent(const types::point_t &position,
                                   TerrainType terrainType)
    : SinglePositionEvent(position), terrainType(terrainType) {}

SingleEditTerrainEvent::~SingleEditTerrainEvent() {}

void SingleEditTerrainEvent::applyEvent(EntitiesManager &entitiesManager,
                                  SelectionManager &) const {
  auto tilePtr = entitiesManager.getTilePtrByPosition(this->getPosition());
  tilePtr->setTerrainType(this->terrainType);
}

} // namespace model
} // namespace how
