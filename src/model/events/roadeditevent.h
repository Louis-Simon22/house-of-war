#ifndef ROADEDITEVENT_H
#define ROADEDITEVENT_H

#include "./modelevent.h"

namespace how {
namespace model {
class RoadEditEvent : public ModelEvent {
public:
  RoadEditEvent(const types::segment_t &segment);

public:
  ~RoadEditEvent() override;

public:
  void applyEvent(EntitiesManager &entitiesManager,
                  SelectionManager &) const override;

private:
  types::segment_t segment;
};
} // namespace model
} // namespace how

#endif // ROADEDITEVENT_H
