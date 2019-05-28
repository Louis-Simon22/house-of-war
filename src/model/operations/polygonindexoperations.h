#ifndef POLYGONINDEXOPERATIONS_H
#define POLYGONINDEXOPERATIONS_H

#include <vector>

#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/strategies/strategies.hpp>

#include "../graphtypes.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
namespace bgi = ::boost::geometry::index;
} // namespace

template <typename Geometry>
std::vector<types::graph_vertex_desc_t>
intersectingGeometry(Geometry geometry,
                     const types::spatial_index_tree_t &spatialIndexTree,
                     const types::graph_t &graph) {
  auto intersectingVertexDescs = std::vector<types::graph_vertex_desc_t>();

  spatialIndexTree.query(bgi::intersects(geometry),
                         boost::make_function_output_iterator(
                             [&geometry, &intersectingVertexDescs,
                              &graph](types::spatial_index_value_t value) {
                               const auto desc = std::get<1>(value);
                               const auto &polygon = graph[desc]->getPolygon();
                               if (bg::intersects(geometry, polygon)) {
                                 intersectingVertexDescs.push_back(desc);
                               }
                             }));

  return intersectingVertexDescs;
}

std::vector<types::graph_vertex_desc_t>
intersectingArea(types::box_t area,
                 const types::spatial_index_tree_t &spatialIndexTree) {
  auto intersectingVertexDescs = std::vector<types::graph_vertex_desc_t>();

  spatialIndexTree.query(bgi::intersects(area),
                         std::back_inserter(intersectingVertexDescs));

  return intersectingVertexDescs;
}

types::graph_vertex_desc_t
coveredByPoint(types::point_t position,
               const types::spatial_index_tree_t &spatialIndexTree,
               const types::graph_t &graph);

} // namespace model
} // namespace how

#endif // POLYGONINDEXOPERATIONS_H
