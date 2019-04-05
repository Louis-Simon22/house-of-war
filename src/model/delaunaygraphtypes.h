#ifndef DELAUNAYGRAPHTYPES_H
#define DELAUNAYGRAPHTYPES_H

#include <boost/graph/adjacency_list.hpp>

#include "./modeltypes.h"
#include "./world/delaunayedge.h"
#include "./world/voronoicell.h"

namespace how {
namespace model {
namespace types {
using delaunay_graph_t = ::boost::adjacency_list<
    ::boost::vecS, ::boost::vecS, ::boost::directedS, ::how::model::VoronoiCell,
    ::how::model::DelaunayEdge, ::boost::no_property, ::boost::vecS>;
using delaunay_graph_vertex_index_t = ::boost::graph_traits<
    ::how::model::types::delaunay_graph_t>::vertex_descriptor;
using delaunay_graph_edge_index_t = ::boost::graph_traits<
    ::how::model::types::delaunay_graph_t>::edge_descriptor;
} // namespace types
} // namespace model
} // namespace how

#endif // DELAUNAYGRAPHTYPES_H
