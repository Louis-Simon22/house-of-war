#ifndef SELECTEVENT_H
#define SELECTEVENT_H

#include "./spatialevent.h"

namespace how {
namespace model {
class SelectEvent : public SpatialEvent {
public:
  SelectEvent(types::coordinate_t posX, types::coordinate_t posY);

public:
  ~SelectEvent() override;

public:
  void applyEvent(EntitiesManager &,
                  SelectionManager &selectionManager) const override;
};
} // namespace model
} // namespace how

#endif // SELECTEVENT_H
