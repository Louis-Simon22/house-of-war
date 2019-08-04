#include "editterrainevent.h"

namespace how {
namespace model {

EditTerrainEvent::EditTerrainEvent(types::coordinate_t posX,
                                   types::coordinate_t posY,
                                   TerrainType terrainType)
    : SpatialEvent(posX, posY), terrainType(terrainType) {}

EditTerrainEvent::~EditTerrainEvent() {}

void EditTerrainEvent::applyEvent(EntitiesManager &entitiesManager,
                                  SelectionManager &) const {
  auto tilePtr = entitiesManager.getTilePtrByPosition(this->getPosition());
  tilePtr->setTerrainType(this->terrainType);
}

} // namespace model
} // namespace how
