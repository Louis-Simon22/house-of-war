#ifndef EDITTERRAINEVENT_H
#define EDITTERRAINEVENT_H

#include "../entities/terrain/terraintype.h"
#include "./singlepositionevent.h"

namespace how {
namespace model {
class SingleEditTerrainEvent : public SinglePositionEvent {
public:
  SingleEditTerrainEvent(const types::point_t &position, TerrainType terrainType);

public:
  ~SingleEditTerrainEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &) const override;

private:
  TerrainType terrainType;
};
} // namespace model
} // namespace how

#endif // EDITTERRAINEVENT_H
