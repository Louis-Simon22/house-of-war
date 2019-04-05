#include "graphmovement.h"

namespace how {
namespace model {
GraphMovement::GraphMovement(
    const types::delaunay_graph_t *const delaunayGraph,
    GraphEntity *const entity,
    std::vector<types::delaunay_graph_vertex_index_t> destinations)
    : delaunayGraph(delaunayGraph), entity(entity), destinations(destinations),
      currentDestination(0) {}

GraphMovement::~GraphMovement() {}

bool GraphMovement::progress(float deltaTime) {
  const auto &destinationVoronoiCell = this->delaunayGraph->operator[](
      this->destinations[this->currentDestination]);
  this->entity->position = destinationVoronoiCell.centroid;
  this->currentDestination++;
  // TODO how to uniquely identify characters through deletion
//  changeSignal(this->);
  return this->currentDestination >= this->destinations.size();
}

void GraphMovement::destinationReached() {}
} // namespace model
} // namespace how
