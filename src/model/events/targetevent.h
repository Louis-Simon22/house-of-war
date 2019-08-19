#ifndef TARGETEVENT_H
#define TARGETEVENT_H

#include "./modelevent.h"

namespace how {
namespace model {
class TargetEvent : public ModelEvent {
public:
  TargetEvent(const types::point_t &position);
  ~TargetEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &selectionManager) const;

private:
  types::point_t position;
};
} // namespace model
} // namespace how

#endif // TARGETEVENT_H
