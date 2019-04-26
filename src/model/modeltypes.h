#ifndef MODELTYPES_H
#define MODELTYPES_H

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/segment.hpp>

namespace how {
namespace types {

using characteristics_t = float;
using coordinate_t = float;
using coordinate_fpt_t = float;
using point_t =
    ::boost::geometry::model::point<coordinate_t, 2,
                                    ::boost::geometry::cs::cartesian>;
using segment_t = ::boost::geometry::model::segment<point_t>;
using box_t = ::boost::geometry::model::box<point_t>;
// TODO why is clockwise false?
using polygon_t = ::boost::geometry::model::polygon<point_t, false, true>;
using ring_t = ::boost::geometry::model::ring<point_t, true, true>;

} // namespace types
} // namespace how

#endif // MODELTYPES_H
