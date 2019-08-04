#include "spatialevent.h"

namespace how {
namespace model {

SpatialEvent::SpatialEvent(types::coordinate_t posX, types::coordinate_t posY)
    : ModelEvent(), position(posX, posY) {}

SpatialEvent::~SpatialEvent() {}

const types::point_t &SpatialEvent::getPosition() const {
  return this->position;
}

} // namespace model
} // namespace how
