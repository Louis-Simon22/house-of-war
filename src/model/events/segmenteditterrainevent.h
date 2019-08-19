#ifndef SEGMENTEDITTERRAINEVENT_H
#define SEGMENTEDITTERRAINEVENT_H

#include "../entities/terrain/terraintype.h"
#include "./modelevent.h"

namespace how {
namespace model {
class SegmentEditTerrainEvent : public ModelEvent {
public:
  SegmentEditTerrainEvent(const types::segment_t &segment,
                          TerrainType terrainType);

public:
  ~SegmentEditTerrainEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &) const override;

private:
  types::segment_t segment;
  TerrainType terrainType;
};
} // namespace model
} // namespace how

#endif // SEGMENTEDITTERRAINEVENT_H
