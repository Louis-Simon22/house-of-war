#include "pathfindingoperations.h"

#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/transform_value_property_map.hpp>

#include "../entities/delaunayedge.h"
#include "../operations/graphoperations.h"

namespace how {
namespace model {

GraphEntityPositionChange *
graphEntityPathfinding(const types::graph_t *graphPtr,
                       GraphEntity &movingEntity,
                       types::graph_vertex_desc_t destinationVertexDesc) {
  const auto &graph = *graphPtr;
  const auto &entityVertexIndex = movingEntity.getCurrentVertexDesc();

  // Map of the of the shortest path by predecessors
  std::vector<types::graph_vertex_desc_t> predecessors;
  std::tie(predecessors, std::ignore) = computeDijkstra<>(
      entityVertexIndex,
      [](const DelaunayEdge &edge) -> types::coordinate_t {
        return edge.getDistanceWalking();
      },
      graph);

  // Find the current vertex in the predecessors map starting from the
  // destination vertex
  auto destinations = std::vector<types::graph_vertex_desc_t>();
  auto currentVertexIndex = destinationVertexDesc;
  while (currentVertexIndex != entityVertexIndex) {
    destinations.push_back(currentVertexIndex);
    currentVertexIndex = predecessors[currentVertexIndex];
  }
  // Reverse the destinations list since it was obtained from a predecessors
  // map
  std::reverse(destinations.begin(), destinations.end());

  return new GraphEntityPositionChange(graphPtr, movingEntity, destinations);
}

} // namespace model
} // namespace how
