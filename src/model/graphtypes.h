#ifndef graphtypes_H
#define graphtypes_H

#include <memory>

#include <boost/geometry/index/rtree.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "./entities/delaunayedge.h"
#include "./entities/voronoicell.h"
#include "./modeltypes.h"

namespace how {
namespace types {
using graph_t =
    ::boost::adjacency_list<::boost::vecS, ::boost::vecS, ::boost::directedS,
                            std::shared_ptr<::how::model::VoronoiCell>,
                            std::shared_ptr<::how::model::DelaunayEdge>,
                            ::boost::no_property, ::boost::vecS>;
using graph_vertex_desc_t = ::boost::graph_traits<graph_t>::vertex_descriptor;
using graph_edge_desc_t = ::boost::graph_traits<graph_t>::edge_descriptor;
using graph_edge_iterator_t = ::boost::graph_traits<graph_t>::edge_iterator;
using graph_vertex_iterator_t = ::boost::graph_traits<graph_t>::vertex_iterator;

using spatial_index_value_t = std::pair<types::box_t, graph_vertex_desc_t>;
using spatial_index_tree_t =
    ::boost::geometry::index::rtree<spatial_index_value_t,
                                    ::boost::geometry::index::quadratic<16>>;
} // namespace types
} // namespace how

#endif // graphtypes_H
