#ifndef SINGLEEDITTERRAINEVENT_H
#define SINGLEEDITTERRAINEVENT_H

#include "../entities/terrain/terraintype.h"
#include "./modelevent.h"

namespace how {
namespace model {
class SingleEditTerrainEvent : public ModelEvent {
public:
  SingleEditTerrainEvent(const types::point_t &position,
                         TerrainType terrainType);

public:
  ~SingleEditTerrainEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &) const override;

private:
  types::point_t position;
  TerrainType terrainType;
};
} // namespace model
} // namespace how

#endif // SINGLEEDITTERRAINEVENT_H
