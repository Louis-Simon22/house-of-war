#include "polygonindexoperations.h"

#include <boost/geometry/algorithms/covered_by.hpp>

namespace how {
namespace model {

types::graph_vertex_desc_t
coveredByPoint(types::point_t position,
               const types::spatial_index_tree_t &spatialIndexTree,
               const types::graph_t &graph) {
  auto coveredValues = std::vector<types::spatial_index_value_t>();

  spatialIndexTree.query(bgi::intersects(position),
                         std::back_inserter(coveredValues));

  for (const auto &coveredValue : coveredValues) {
    const auto desc = std::get<1>(coveredValue);
    const auto &polygon = graph[desc]->getPolygon();
    if (bg::covered_by(position, polygon)) {
      return desc;
    }
  }

  // TODO handle this nothing found case
  return std::numeric_limits<types::graph_vertex_desc_t>::max();
}

} // namespace model
} // namespace how
