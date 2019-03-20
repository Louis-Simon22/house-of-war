#include "progressivemovement.h"

namespace how {
namespace model {
ProgressiveMovement::ProgressiveMovement(
    const types::delaunay_graph_t *const delaunayGraph, GraphEntity *entity,
    std::vector<const types::delaunay_graph_vertex_index_t *> destinations)
    : delaunayGraph(delaunayGraph), entity(entity), destinations(destinations),
      currentDestination(0) {}

ProgressiveMovement::~ProgressiveMovement() {}

bool ProgressiveMovement::progress(float deltaTime) {
  const auto &destinationVoronoiCell = this->delaunayGraph->operator[](
      *this->destinations[this->currentDestination]);
  this->entity->position = destinationVoronoiCell.centroid;
  this->currentDestination++;
  return this->currentDestination >= this->destinations.size();
}

void ProgressiveMovement::destinationReached() {}
} // namespace model
} // namespace how
