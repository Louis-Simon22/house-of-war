#include "polygonindexoperations.h"

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {

types::graph_vertex_desc_t
cellDescAtPosition(const types::graph_t *graph,
                   const types::polygon_index_tree_t *polygonIndexTree,
                   types::point_t position) {
  auto intersectingIndices = std::vector<types::polygon_index_t>();

  polygonIndexTree->query(bgi::intersects(position),
                          std::back_inserter(intersectingIndices));
  for (const auto &intersectingIndex : intersectingIndices) {
    const auto &desc = std::get<1>(intersectingIndex);
    const auto &polygon = graph->operator[](desc).getPolygon();
    if (bg::covered_by(position, polygon)) {
      return desc;
    }
  }

  // TODO handle this nothing found case
  return std::numeric_limits<types::graph_vertex_desc_t>::max();
}

} // namespace model
} // namespace how
