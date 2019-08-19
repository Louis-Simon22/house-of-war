#ifndef BOXSELECTEVENT_H
#define BOXSELECTEVENT_H

#include "./modelevent.h"

namespace how {
namespace model {
class BoxSelectEvent : public ModelEvent {
public:
  BoxSelectEvent(const types::box_t &box, bool addToSelection);

public:
  ~BoxSelectEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &selectionManager) const override;

private:
  types::box_t box;
  bool addToSelection;
};
} // namespace model
} // namespace how

#endif // BOXSELECTEVENT_H
