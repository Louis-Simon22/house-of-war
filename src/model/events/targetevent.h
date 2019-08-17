#ifndef TARGETEVENT_H
#define TARGETEVENT_H

#include "./singlepositionevent.h"

namespace how {
namespace model {
class TargetEvent : public SinglePositionEvent {
public:
  TargetEvent(const types::point_t &position);

public:
  ~TargetEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &selectionManager) const;
};
} // namespace model
} // namespace how

#endif // TARGETEVENT_H
