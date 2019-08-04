#ifndef EDITTERRAINEVENT_H
#define EDITTERRAINEVENT_H

#include "../entities/terrain/terraintype.h"
#include "./spatialevent.h"

namespace how {
namespace model {
class EditTerrainEvent : public SpatialEvent {
public:
  EditTerrainEvent(types::coordinate_t posX, types::coordinate_t posY,
                   TerrainType terrainType);

public:
  ~EditTerrainEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &) const override;

private:
  TerrainType terrainType;
};
} // namespace model
} // namespace how

#endif // EDITTERRAINEVENT_H
