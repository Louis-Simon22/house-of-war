#ifndef MODELTYPES_H
#define MODELTYPES_H

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/polygon/voronoi.hpp>

namespace how {
namespace model {
namespace types {

using coordinate_t = long long;
using coordinate_fpt_t = double;
using point_t =
    ::boost::geometry::model::point<coordinate_t, 2,
                                    ::boost::geometry::cs::cartesian>;
using segment_t = ::boost::geometry::model::segment<point_t>;
using box_t = ::boost::geometry::model::box<point_t>;

struct WorldGenerationConfig {
  coordinate_t minCornerX;
  coordinate_t minCornerY;
  coordinate_t maxCornerX;
  coordinate_t maxCornerY;
};

using vd_t = ::boost::polygon::voronoi_diagram<coordinate_fpt_t>;
} // namespace types
} // namespace model
} // namespace how

#endif // MODELTYPES_H
