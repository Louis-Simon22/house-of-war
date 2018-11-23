#ifndef MODELTYPES_H
#define MODELTYPES_H

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>

namespace how {
namespace model {
namespace types {
using coordinate_t = int;
using point_t =
    ::boost::geometry::model::point<coordinate_t, 2, ::boost::geometry::cs::cartesian>;
using box_t = ::boost::geometry::model::box<point_t>;

struct WorldGenerationConfig {
  coordinate_t minCornerX;
  coordinate_t minCornerY;
  coordinate_t maxCornerX;
  coordinate_t maxCornerY;
};
}  // namespace types
}  // namespace model
}  // namespace how

#endif  // MODELTYPES_H
