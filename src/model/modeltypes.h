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
} // namespace types
} // namespace model
} // namespace how

namespace boost {
namespace polygon {

template <> struct geometry_concept<::how::model::types::point_t> {
  typedef point_concept type;
};

template <> struct point_traits<::how::model::types::point_t> {
  typedef typename ::how::model::types::coordinate_t coordinate_type;

  static inline coordinate_type get(const ::how::model::types::point_t &point,
                                    orientation_2d orient) {
    return orient == HORIZONTAL ? ::boost::geometry::get<0>(point)
                                : ::boost::geometry::get<1>(point);
  }
};

template <> struct point_mutable_traits<::how::model::types::point_t> {
  typedef typename ::how::model::types::coordinate_t coordinate_type;

  static void set(::how::model::types::point_t &point, orientation_2d orient,
                  coordinate_type value) {
    if (orient == HORIZONTAL) {
      ::boost::geometry::set<0>(point, value);
    } else {
      ::boost::geometry::set<1>(point, value);
    }
  }
  static ::how::model::types::point_t construct(coordinate_type x_value,
                                                coordinate_type y_value) {
    return ::how::model::types::point_t(x_value, y_value);
  }
};

template <> struct geometry_concept<::how::model::types::segment_t> {
  typedef segment_concept type;
};

template <> struct segment_traits<::how::model::types::segment_t> {
  typedef typename ::how::model::types::coordinate_t coordinate_type;
  typedef typename ::how::model::types::point_t point_type;

  static inline point_type get(const ::how::model::types::segment_t &segment,
                               direction_1d dir) {
    return dir.to_int() ? segment.second : segment.first;
  }
};

template <> struct segment_mutable_traits<::how::model::types::segment_t> {
  typedef typename ::how::model::types::coordinate_t coordinate_type;
  typedef typename ::how::model::types::point_t point_type;

  static inline void set(::how::model::types::segment_t &segment,
                         direction_1d dir, const point_type &point) {
    if (dir.to_int()) {
      ::boost::geometry::set<1, 0>(segment, ::boost::geometry::get<0>(point));
      ::boost::geometry::set<1, 1>(segment, ::boost::geometry::get<1>(point));
    } else {
      ::boost::geometry::set<0, 0>(segment, ::boost::geometry::get<0>(point));
      ::boost::geometry::set<0, 1>(segment, ::boost::geometry::get<1>(point));
    }
  }

  static inline ::how::model::types::segment_t
  construct(const point_type &low, const point_type &high) {
    return ::how::model::types::segment_t(low, high);
  }
};

struct my_ulp_comparison {
  enum Result { LESS = -1, EQUAL = 0, MORE = 1 };
  Result operator()(::how::model::types::coordinate_t a,
                    ::how::model::types::coordinate_t b,
                    unsigned int maxUlps) const {
    if (a < b) {
      return LESS;
    } else if (a > b) {
      return MORE;
    } else {
      return EQUAL;
    }
  }
};

struct my_voronoi_diagram_traits {
  typedef ::how::model::types::coordinate_t coordinate_type;
  typedef voronoi_cell<coordinate_type> cell_type;
  typedef voronoi_vertex<coordinate_type> vertex_type;
  typedef voronoi_edge<coordinate_type> edge_type;
  typedef struct {
  public:
    enum { ULPS = 128 };
    bool operator()(const vertex_type &v1, const vertex_type &v2) const {
      return ulp_cmp(v1.x(), v2.x(), ULPS) ==
                 ::boost::polygon::my_ulp_comparison::EQUAL &&
             ulp_cmp(v1.y(), v2.y(), ULPS) ==
                 ::boost::polygon::my_ulp_comparison::EQUAL;
    }

  private:
    my_ulp_comparison ulp_cmp;
  } vertex_equality_predicate_type;
};
} // namespace polygon
} // namespace boost

namespace how {
namespace model {
namespace types {
using vd_t = ::boost::polygon::voronoi_diagram<
    coordinate_t, ::boost::polygon::my_voronoi_diagram_traits>;
} // namespace types
} // namespace model
} // namespace how

#endif // MODELTYPES_H
