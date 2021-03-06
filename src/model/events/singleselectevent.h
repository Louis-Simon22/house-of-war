#ifndef SINGLESELECTEVENT_H
#define SINGLESELECTEVENT_H

#include "./modelevent.h"

namespace how {
namespace model {
class SingleSelectEvent : public ModelEvent {
public:
  SingleSelectEvent(const types::point_t &position, bool addToSelection);
  ~SingleSelectEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &selectionManager) const override;

private:
  types::point_t position;
  bool addToSelection;
};
} // namespace model
} // namespace how

#endif // SINGLESELECTEVENT_H
