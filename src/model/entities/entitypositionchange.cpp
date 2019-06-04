#include "entitypositionchange.h"

namespace how {
namespace model {

EntityPositionChange::EntityPositionChange(
    Entity *entity, std::vector<const VoronoiCell *> destinations)
    : entity(entity), destinations(destinations), currentDestinationIndex(0) {}

EntityPositionChange::~EntityPositionChange() {}

bool EntityPositionChange::progress() {
  const auto *destinationVoronoiCellPtr =
      this->destinations[this->currentDestinationIndex];
  this->entity->setPosition(destinationVoronoiCellPtr->getPosition());
  this->currentDestinationIndex++;
  return this->currentDestinationIndex >= this->destinations.size();
}

void EntityPositionChange::destinationReached() {}

} // namespace model
} // namespace how
