#include "graphentitypositionchange.h"

namespace how {
namespace model {

GraphEntityPositionChange::GraphEntityPositionChange(
    const types::graph_t &delaunayGraph, GraphEntity &graphEntity,
    std::vector<types::graph_vertex_desc_t> destinations)
    : delaunayGraph(delaunayGraph), graphEntity(graphEntity), destinations(destinations),
      currentDestinationIndex(0) {}

GraphEntityPositionChange::~GraphEntityPositionChange() {}

bool GraphEntityPositionChange::progress(float deltaTime) {
  const auto &currentDestination =
      this->destinations[this->currentDestinationIndex];
  const auto &destinationVoronoiCell = this->delaunayGraph[currentDestination];
  this->graphEntity.setPosition(destinationVoronoiCell.getCenter());
  this->currentDestinationIndex++;
  return this->currentDestinationIndex >= this->destinations.size();
}

void GraphEntityPositionChange::destinationReached() {}

} // namespace model
} // namespace how
