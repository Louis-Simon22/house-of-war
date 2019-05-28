#include "graphentitypositionchange.h"

namespace how {
namespace model {

GraphEntityPositionChange::GraphEntityPositionChange(
    GraphEntity *graphEntity, std::vector<VoronoiCell *> destinations)
    : graphEntity(graphEntity), destinations(destinations),
      currentDestinationIndex(0) {}

GraphEntityPositionChange::~GraphEntityPositionChange() {}

bool GraphEntityPositionChange::progress() {
  const auto *destinationVoronoiCellPtr =
      this->destinations[this->currentDestinationIndex];
  this->graphEntity->setPosition(destinationVoronoiCellPtr->getPosition());
  this->currentDestinationIndex++;
  return this->currentDestinationIndex >= this->destinations.size();
}

void GraphEntityPositionChange::destinationReached() {}

} // namespace model
} // namespace how
