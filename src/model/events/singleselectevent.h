#ifndef SELECTEVENT_H
#define SELECTEVENT_H

#include "./singlepositionevent.h"

namespace how {
namespace model {
class SingleSelectEvent : public SinglePositionEvent {
public:
  SingleSelectEvent(const types::point_t &position);

public:
  ~SingleSelectEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &selectionManager) const override;
};
} // namespace model
} // namespace how

#endif // SELECTEVENT_H
