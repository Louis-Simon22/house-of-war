#ifndef graphtypes_H
#define graphtypes_H

#include <memory>

#include <boost/graph/adjacency_list.hpp>

#include "./modeltypes.h"

namespace how {
namespace model {
class VoronoiCell;
class DelaunayEdge;
} // namespace model

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

} // namespace types
} // namespace how

#include "./entities/delaunayedge.h"
#include "./entities/voronoicell.h"

#endif // graphtypes_H
