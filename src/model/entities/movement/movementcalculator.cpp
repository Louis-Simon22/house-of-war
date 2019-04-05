#include "movementcalculator.h"

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/transform_value_property_map.hpp>

#include "../../world/delaunayedge.h"
#include "./movementweightcalculator.h"

namespace how {
namespace model {

GraphMovement *
calculateMovement(const types::delaunay_graph_t *graphPtr, GraphEntity *movingEntity,
             types::delaunay_graph_vertex_index_t destionationVertexIndex) {
  const auto &graph = *graphPtr;
  const auto &entityVertexIndex = movingEntity->getCurrentVertexIndex();

  auto predecessors = std::vector<types::delaunay_graph_vertex_index_t>(
      ::boost::num_vertices(graph));
  auto weightMap = ::boost::make_transform_value_property_map(
      &MovementWeightCalculator::calculateEdgeWeight,
      ::boost::get(boost::edge_bundle, graph));
  ::boost::dijkstra_shortest_paths(
      graph, entityVertexIndex,
      ::boost::predecessor_map(&predecessors[0]).weight_map(weightMap));

  auto destinations = std::vector<types::delaunay_graph_vertex_index_t>();
  auto currentVertexIndex = destionationVertexIndex;
  while (currentVertexIndex != entityVertexIndex) {
    destinations.push_back(currentVertexIndex);
    currentVertexIndex = predecessors[currentVertexIndex];
  }

  return new GraphMovement(graphPtr, movingEntity, destinations);
}

} // namespace model
} // namespace how
