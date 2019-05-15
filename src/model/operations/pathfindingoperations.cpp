#include "pathfindingoperations.h"

#include <algorithm>

#include "../entities/delaunayedge.h"
#include "../operations/graphoperations.h"

namespace how {
namespace model {

GraphEntityPositionChange *
graphEntityPathfinding(GraphEntity &sourceEntity,
                       types::graph_vertex_desc_t destinationVertexDesc,
                       const types::graph_t &graph) {
  const auto sourceVertexDesc = 1; // sourceEntity.getCurrentVertexDesc();

  // Map of the shortest path by predecessors
  std::vector<types::graph_vertex_desc_t> predecessors;
  std::tie(predecessors, std::ignore) = computeDijkstra<>(
      sourceVertexDesc,
      [](const DelaunayEdge &edge) -> types::coordinate_t {
        return edge.getDistanceWalking();
      },
      graph);

  // Find the current vertex in the predecessors map starting from the
  // destination vertex
  auto destinations = std::vector<types::graph_vertex_desc_t>();
  auto currentVertexIndex = destinationVertexDesc;
  while (currentVertexIndex != sourceVertexDesc) {
    destinations.push_back(currentVertexIndex);
    currentVertexIndex = predecessors[currentVertexIndex];
  }
  // Reverse the destinations list since it was obtained from a predecessors
  // map
  std::reverse(destinations.begin(), destinations.end());

  return new GraphEntityPositionChange(graph, sourceEntity, destinations);
}

} // namespace model
} // namespace how
