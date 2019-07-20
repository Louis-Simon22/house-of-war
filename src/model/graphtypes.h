#ifndef GRAPHTYPES_H
#define GRAPHTYPES_H

#include <memory>

#include <boost/graph/adjacency_list.hpp>

#include "./entities/terrain/delaunayedge.h"
#include "./entities/terrain/tile.h"
#include "./modeltypes.h"

namespace how {
namespace types {
using graph_t =
    ::boost::adjacency_list<::boost::vecS, ::boost::vecS, ::boost::directedS,
                            std::shared_ptr<::how::model::Tile>,
                            std::shared_ptr<::how::model::DelaunayEdge>,
                            ::boost::no_property, ::boost::vecS>;
using graph_vertex_desc_t = ::boost::graph_traits<graph_t>::vertex_descriptor;
using graph_edge_desc_t = ::boost::graph_traits<graph_t>::edge_descriptor;
using graph_edge_iterator_t = ::boost::graph_traits<graph_t>::edge_iterator;
using graph_vertex_iterator_t = ::boost::graph_traits<graph_t>::vertex_iterator;
} // namespace types
} // namespace how

#endif // GRAPHTYPES_H
