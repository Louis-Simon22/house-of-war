#include "pathfindingoperations.h"

#include "../entities/terrain/delaunayedge.h"
#include "../operations/graphoperations.h"

namespace how {
namespace model {

std::vector<types::point_t>
graphEntityPathfinding(types::graph_vertex_desc_t sourceVertexDesc,
                       types::graph_vertex_desc_t destinationVertexDesc,
                       const types::graph_t &graph) {
  // Map of the shortest path by predecessors
  std::vector<types::graph_vertex_desc_t> predecessors;
  std::tie(predecessors, std::ignore) = computeDijkstra<>(
      sourceVertexDesc,
      [&graph](
          const std::shared_ptr<DelaunayEdge> &edgePtr) -> types::coordinate_t {
        const auto &edgeDesc = edgePtr->getEdgeDesc();
        auto sourceVoronoiCellPtr = graph[::boost::source(edgeDesc, graph)];
        auto targetVoronoiCellPtr = graph[::boost::target(edgeDesc, graph)];
        return edgePtr->getWalkingDistance();
      },
      graph);

  // Find the current vertex in the predecessors map starting from the
  // destination vertex
  auto destinations = std::vector<types::point_t>();
  auto currentVertexIndex = destinationVertexDesc;
  while (currentVertexIndex != sourceVertexDesc) {
    destinations.push_back(graph[currentVertexIndex]->getPosition());
    currentVertexIndex = predecessors[currentVertexIndex];
  }

  // Reverse the destinations because they were obtained from a map of
  // predecessors
  std::reverse(destinations.begin(), destinations.end());

  return destinations;
}

} // namespace model
} // namespace how
