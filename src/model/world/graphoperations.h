#ifndef GRAPHOPERATIONS_H
#define GRAPHOPERATIONS_H

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/transform_value_property_map.hpp>

#include "../delaunaygraphtypes.h"

namespace how {
namespace model {

template <typename WeightCalculator>
std::pair<std::vector<types::delaunay_graph_vertex_desc_t>,
          std::vector<types::coordinate_t>>
computeDijkstra(const types::delaunay_graph_t &graph,
                types::delaunay_graph_vertex_desc_t source,
                const WeightCalculator &weightCalculator) {
  // Map of the of the shortest path by predecessors (so in reverse order)
  auto predecessors = std::vector<types::delaunay_graph_vertex_desc_t>(
      ::boost::num_vertices(graph));
  // Map of the distances from each vertex to the source
  auto distanceMap =
      std::vector<types::coordinate_t>(::boost::num_vertices(graph));
  // Map of the weights of each edge
  auto weightMap = ::boost::make_transform_value_property_map(
      weightCalculator, ::boost::get(boost::edge_bundle, graph));

  ::boost::dijkstra_shortest_paths(graph, source,
                                   ::boost::predecessor_map(&predecessors[0])
                                       .distance_map(&distanceMap[0])
                                       .weight_map(weightMap));

  return std::pair<std::vector<types::delaunay_graph_vertex_desc_t>,
                   std::vector<types::coordinate_t>>(predecessors, distanceMap);
}
} // namespace model
} // namespace how
#endif // GRAPHOPERATIONS_H
