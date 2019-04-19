#include "graphmovement.h"

namespace how {
namespace model {
GraphMovement::GraphMovement(
    const types::graph_t *const delaunayGraph,
    GraphEntity *const entity,
    std::vector<types::graph_vertex_desc_t> destinations)
    : delaunayGraph(delaunayGraph), entity(entity), destinations(destinations),
      currentDestinationIndex(0) {}

GraphMovement::~GraphMovement() {}

bool GraphMovement::progress(float deltaTime) {
  const auto &currentDestionation =
      this->destinations[this->currentDestinationIndex];
  const auto &destinationVoronoiCell =
      this->delaunayGraph->operator[](currentDestionation);
  this->entity->position = destinationVoronoiCell.centroid;
  this->entity->setCurrentVertex(currentDestionation);
  this->currentDestinationIndex++;
  changeSignal(this->entity->uuid);
  return this->currentDestinationIndex >= this->destinations.size();
}

void GraphMovement::destinationReached() {
}
} // namespace model
} // namespace how
