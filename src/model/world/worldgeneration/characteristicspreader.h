#ifndef CHARACTERISTICSPREADER_H
#define CHARACTERISTICSPREADER_H

#include "../../delaunaygraphtypes.h"
#include "../../easingfunctions.h"
#include "../graphoperations.h"

namespace how {
namespace model {

template <typename CharacteristicAssignmentFunction>
void spreadCharacteristic(
    types::delaunay_graph_vertex_desc_t sourceVertexDesc,
    CharacteristicAssignmentFunction characteristicAssignmentFunction,
    types::delaunay_graph_t& graph) {
  std::vector<types::coordinate_t> distances;
  std::tie(std::ignore, distances) = computeDijkstra(
      graph, sourceVertexDesc,
      [](DelaunayEdge) -> types::coordinate_fpt_t { return 1; });
  const auto &greatestDistance =
      *std::max_element(distances.begin(), distances.end());
  for (std::size_t vertexDesc = 0; vertexDesc < distances.size(); vertexDesc++) {
    const auto &distance = distances[vertexDesc];
    const auto value = normalize(distance, 0, greatestDistance);
    characteristicAssignmentFunction(value, vertexDesc, graph);
  }
}

} // namespace model
} // namespace how

#endif // CHARACTERISTICSPREADER_H
