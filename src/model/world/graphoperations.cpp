#include "graphoperations.h"

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

types::graph_vertex_desc_t
nearestVoronoiCell(types::point_t point, types::graph_t &graph) {
  const auto &vertexSet = graph.vertex_set();
  for (const auto vertexDesc : vertexSet) {
    if (bg::covered_by(point, graph[vertexDesc].polygon)) {
      return vertexDesc;
    }
  }
  return 0;
}

} // namespace model
} // namespace how
