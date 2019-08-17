#ifndef SINGLEPOSITIONEVENT_H
#define SINGLEPOSITIONEVENT_H

#include "./modelevent.h"

namespace how {
namespace model {
class SinglePositionEvent : public ModelEvent {
public:
  SinglePositionEvent(const types::point_t &position);

public:
  virtual ~SinglePositionEvent() = 0;

protected:
  const types::point_t &getPosition() const;

private:
  types::point_t position;
};
} // namespace model
} // namespace how

#endif // SINGLEPOSITIONEVENT_H
