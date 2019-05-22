#include "pathfindingoperations.h"

#include "../entities/delaunayedge.h"
#include "../operations/graphoperations.h"

#include <iostream>

namespace how {
namespace model {

std::vector<VoronoiCell *>
graphEntityPathfinding(types::graph_vertex_desc_t sourceVertexDesc,
                       types::graph_vertex_desc_t destinationVertexDesc,
                       types::graph_t &graph) {
  // Map of the shortest path by predecessors
  std::vector<types::graph_vertex_desc_t> predecessors;
  std::tie(predecessors, std::ignore) = computeDijkstra<>(
      sourceVertexDesc,
      [](const std::shared_ptr<DelaunayEdge> &edgePtr) -> types::coordinate_t {
        return 1;
        //        return edgePtr->getDistanceWalking();
      },
      graph);

  std::cout << "Source : " << sourceVertexDesc << std::endl;
  std::cout << "Destination : " << destinationVertexDesc << std::endl;
  // Find the current vertex in the predecessors map starting from the
  // destination vertex
  auto destinations = std::vector<VoronoiCell *>();
  auto currentVertexIndex = destinationVertexDesc;
  while (currentVertexIndex != sourceVertexDesc) {
    destinations.push_back(graph[currentVertexIndex].get());
    currentVertexIndex = predecessors[currentVertexIndex];
    std::cout << currentVertexIndex << std::endl;
  }
  std::cout << "======" << std::endl;
  // Reverse the destinations list since it was obtained from a predecessors
  // map
  std::reverse(destinations.begin(), destinations.end());

  return destinations;
}

} // namespace model
} // namespace how
