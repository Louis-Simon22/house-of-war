#include "movementcalculator.h"

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/transform_value_property_map.hpp>

#include "../../world/delaunayedge.h"
#include "./movementweightcalculator.h"

namespace how {
namespace model {

ProgressiveMovement moveEntityTo(const types::delaunay_graph_t *graphPtr,
                                 GraphEntity *movingEntity,
                                 const GraphEntity *destination) {
  const auto &graph = *graphPtr;
  const auto *vertexIndex = movingEntity->getCurrentVertexIndex();

  auto predecessors =
      std::vector<types::delaunay_graph_vertex_index_t>(::boost::num_vertices(graph));
  auto weightMap = ::boost::make_transform_value_property_map(
      &MovementWeightCalculator::calculateEdgeWeight,
      ::boost::get(boost::edge_bundle, graph));
  ::boost::dijkstra_shortest_paths(
      graph, *vertexIndex,
      ::boost::predecessor_map(&predecessors[0]).weight_map(weightMap));

  auto destinations = std::vector<const types::delaunay_graph_vertex_index_t *>();
  auto *currentVertexIndex = destination->getCurrentVertexIndex();
  while (currentVertexIndex != movingEntity->getCurrentVertexIndex()) {
    destinations.push_back(currentVertexIndex);
    currentVertexIndex = &predecessors[*currentVertexIndex];
  }

  return ProgressiveMovement(graphPtr, movingEntity, destinations);
}

} // namespace model
} // namespace how
