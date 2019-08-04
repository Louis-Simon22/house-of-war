#ifndef TARGETEVENT_H
#define TARGETEVENT_H

#include "./spatialevent.h"

namespace how {
namespace model {
class TargetEvent : public SpatialEvent {
public:
  TargetEvent(types::coordinate_t posX, types::coordinate_t posY);

public:
  ~TargetEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &selectionManager) const;
};
} // namespace model
} // namespace how

#endif // TARGETEVENT_H
