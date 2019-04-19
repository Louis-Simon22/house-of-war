#include "movementcalculator.h"

#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/transform_value_property_map.hpp>

#include "../../world/delaunayedge.h"
#include "../../world/graphoperations.h"

namespace how {
namespace model {

GraphMovement *
calculateMovement(const types::graph_t *graphPtr,
                  GraphEntity *movingEntity,
                  types::graph_vertex_desc_t destinationVertexDesc) {
  const auto &graph = *graphPtr;
  const auto &entityVertexIndex = movingEntity->getCurrentVertexIndex();

  // Map of the of the shortest path by predecessors
  std::vector<types::graph_vertex_desc_t> predecessors;
  std::tie(predecessors, std::ignore) = computeDijkstra<>(
      entityVertexIndex,
      [&graph](const DelaunayEdge &edge) -> types::coordinate_fpt_t {
//        ::boost::target(edge, graph);
        return edge.distance;
      },
      graph);

  // Find the current vertex in the predecessors map starting from the
  // destionation vertex
  auto destinations = std::vector<types::graph_vertex_desc_t>();
  auto currentVertexIndex = destinationVertexDesc;
  while (currentVertexIndex != entityVertexIndex) {
    destinations.push_back(currentVertexIndex);
    currentVertexIndex = predecessors[currentVertexIndex];
  }
  // Reverse the destionations list since it was obtained from a predecessors
  // map
  std::reverse(destinations.begin(), destinations.end());

  return new GraphMovement(graphPtr, movingEntity, destinations);
}

} // namespace model
} // namespace how
