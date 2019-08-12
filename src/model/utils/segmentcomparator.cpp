#include "segmentcomparator.h"

#include <boost/geometry/algorithms/centroid.hpp>
#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/strategies/strategies.hpp>

#include "./pointcomparator.h"

namespace how {
namespace model {

bool SegmentComparator::operator()(const types::segment_t &s1,
                                   const types::segment_t &s2) const {
  auto centroid1 = types::point_t();
  auto centroid2 = types::point_t();
  bg::centroid(s1, centroid1);
  bg::centroid(s2, centroid2);
  return PointComparator()(centroid1, centroid2);
}

} // namespace model
} // namespace how
