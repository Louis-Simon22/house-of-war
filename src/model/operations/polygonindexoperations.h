#ifndef POLYGONINDEXOPERATIONS_H
#define POLYGONINDEXOPERATIONS_H

#include <vector>

#include "../graphtypes.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
namespace bgi = ::boost::geometry::index;
} // namespace

types::graph_vertex_desc_t
cellDescAtPosition(const types::graph_t *graph,
                   const types::polygon_index_tree_t *polygonIndexTree,
                   types::point_t position);

template <typename Geometry>
std::vector<types::graph_vertex_desc_t>
cellDescsInArea(const types::polygon_index_tree_t *polygonIndexTree,
                Geometry area) {
  auto intersectingIndices = std::vector<types::polygon_index_t>();
  auto cellDescsInArea = std::vector<types::graph_vertex_desc_t>();

  polygonIndexTree->query(bgi::intersects(area),
                          std::back_inserter(intersectingIndices));
  for (const auto &intersectingIndex : intersectingIndices) {
    const auto &desc = std::get<1>(intersectingIndex);
    cellDescsInArea.push_back(desc);
  }

  return cellDescsInArea;
}

} // namespace model
} // namespace how

#endif // POLYGONINDEXOPERATIONS_H
