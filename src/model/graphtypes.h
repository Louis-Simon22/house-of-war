#ifndef GRAPHTYPES_H
#define GRAPHTYPES_H

#include "./modeltypes.h"
#include "./world/voronoicell.h"
#include "./world/delaunayedge.h"

namespace how {
namespace model {
namespace types {
using delaunay_graph_t = ::boost::adjacency_list<
    ::boost::vecS, ::boost::vecS, ::boost::directedS, ::how::model::VoronoiCell,
    ::how::model::DelaunayEdge, ::boost::no_property, ::boost::vecS>;
using delaunay_graph_vertex_t = ::boost::graph_traits<::how::model::types::delaunay_graph_t>::vertex_descriptor;
using delaunay_graph_edge_t = ::boost::graph_traits<::how::model::types::delaunay_graph_t>::edge_descriptor;
}
} // namespace model
} // namespace how

#endif // GRAPHTYPES_H
