#ifndef SPATIALEVENT_H
#define SPATIALEVENT_H

#include "../modeltypes.h"
#include "./modelevent.h"

namespace how {
namespace model {
class SpatialEvent : public ModelEvent {
public:
  SpatialEvent(types::coordinate_t posX, types::coordinate_t posY);

public:
  virtual ~SpatialEvent() = 0;

protected:
  const types::point_t &getPosition() const;

private:
  types::point_t position;
};
} // namespace model
} // namespace how

#endif // SPATIALEVENT_H
