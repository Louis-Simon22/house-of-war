#include "./clockwisepointcomparator.h"

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>

namespace how {
namespace model {

ClockwisePointComparator::ClockwisePointComparator(types::point_t pivot)
    : pivot(pivot) {}

/*
 * Source :
 * https://stackoverflow.com/questions/6989100/sort-points-in-clockwise-order
 */
bool ClockwisePointComparator::operator()(const types::point_t &p1,
                                          const types::point_t &p2) const {
  const auto &x1 = bg::get<0>(p1);
  const auto &x2 = bg::get<0>(p2);
  const auto &xPivot = bg::get<0>(this->pivot);
  if (x1 >= xPivot && x2 < xPivot) {
    return true;
  } else if (x1 < xPivot && x2 >= xPivot) {
    return false;
  } else {
    auto p1ToPivot = p1;
    bg::subtract_point(p1ToPivot, this->pivot);
    auto p2ToPivot = p2;
    bg::subtract_point(p2ToPivot, this->pivot);
    const auto zCrossProduct = bg::get<0>(p1ToPivot) * bg::get<1>(p2ToPivot) -
                               bg::get<1>(p1ToPivot) * bg::get<0>(p2ToPivot);
    return zCrossProduct < 0;
  }
}

} // namespace model
} // namespace how
