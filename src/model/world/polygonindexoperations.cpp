#include "polygonindexoperations.h"

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
namespace bgi = ::boost::geometry::index;
} // namespace

types::graph_vertex_desc_t
cellDescAtPosition(const types::polygon_index_tree_t *polygonIndexTree,
                   types::point_t position) {
  auto intersectingIndices = std::vector<types::polygon_index_t>();

  polygonIndexTree->query(bgi::intersects(position),
                          std::back_inserter(intersectingIndices));
  for (const auto &intersectingIndice : intersectingIndices) {
    const auto &polygon = std::get<0>(intersectingIndice);
    const auto &desc = std::get<1>(intersectingIndice);
    if (bg::covered_by(position, polygon)) {
      return desc;
    }
  }

  return std::numeric_limits<types::graph_vertex_desc_t>::max();
}

} // namespace model
} // namespace how
