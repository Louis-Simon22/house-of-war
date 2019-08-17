#include "singlepositionevent.h"

namespace how {
namespace model {

SinglePositionEvent::SinglePositionEvent(const types::point_t &position)
    : ModelEvent(), position(position) {}

SinglePositionEvent::~SinglePositionEvent() {}

const types::point_t &SinglePositionEvent::getPosition() const {
  return this->position;
}

} // namespace model
} // namespace how
