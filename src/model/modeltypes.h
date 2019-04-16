#ifndef MODELTYPES_H
#define MODELTYPES_H

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/math/quaternion.hpp>

namespace how {
namespace model {
namespace types {

using characteristics_t = float;
using coordinate_t = float;
using coordinate_fpt_t = float;
using point_t =
    ::boost::geometry::model::point<coordinate_t, 2,
                                    ::boost::geometry::cs::cartesian>;
using segment_t = ::boost::geometry::model::segment<point_t>;
using box_t = ::boost::geometry::model::box<point_t>;
using polygon_t = ::boost::geometry::model::polygon<point_t, false, true>;

using quaternion_t = ::boost::math::quaternion<coordinate_fpt_t>;

struct WorldGenerationConfig {
  coordinate_t minCornerX;
  coordinate_t minCornerY;
  coordinate_t maxCornerX;
  coordinate_t maxCornerY;
  coordinate_t minimumVoronoiCellDistance;
  std::uint32_t randomSeed;
};
} // namespace types
} // namespace model
} // namespace how

#endif // MODELTYPES_H
