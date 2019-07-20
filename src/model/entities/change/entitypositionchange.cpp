#include "entitypositionchange.h"

namespace how {
namespace model {

EntityPositionChange::EntityPositionChange(
    Entity *entity, std::vector<types::point_t> destinations)
    : entity(entity), destinations(destinations), currentDestinationIndex(0) {}

EntityPositionChange::~EntityPositionChange() {}

bool EntityPositionChange::progress() {
  this->entity->setPosition(this->destinations[this->currentDestinationIndex]);
  this->currentDestinationIndex++;
  return this->isDone();
}

bool EntityPositionChange::isDone() {
  return this->currentDestinationIndex >= this->destinations.size();
}

} // namespace model
} // namespace how
