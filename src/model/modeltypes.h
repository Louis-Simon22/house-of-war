#ifndef MODELTYPES_H
#define MODELTYPES_H

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/optional.hpp>

namespace how {
namespace model {
namespace types {

using coordinate_t = int;
using coordinate_fpt_t = float;
using point_t =
    ::boost::geometry::model::point<coordinate_t, 2,
                                    ::boost::geometry::cs::cartesian>;
using segment_t = ::boost::geometry::model::segment<point_t>;
using box_t = ::boost::geometry::model::box<point_t>;
using polygon_t = ::boost::geometry::model::polygon<point_t>;

struct WorldGenerationConfig {
  coordinate_t minCornerX;
  coordinate_t minCornerY;
  coordinate_t maxCornerX;
  coordinate_t maxCornerY;
};
} // namespace types
} // namespace model
} // namespace how

// Forward declaration so they can be used in the graph type declaration
namespace how {
namespace model {
struct VoronoiCell;
struct DelaunayEdge;
} // namespace model
} // namespace how

#include "./world/delaunayedge.h"
#include "./world/voronoicell.h"

namespace how {
namespace model {
namespace types {
using delaunayGraph =
    ::boost::adjacency_list<::boost::vecS, ::boost::vecS, ::boost::directedS,
                            ::how::model::VoronoiCell, ::how::model::DelaunayEdge,
                            ::boost::no_property, ::boost::vecS>;
} // namespace types
} // namespace model
} // namespace how

#endif // MODELTYPES_H
