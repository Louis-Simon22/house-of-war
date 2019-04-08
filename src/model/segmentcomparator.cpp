#include "segmentcomparator.h"

#include "./pointcomparator.h"
#include <boost/geometry/algorithms/centroid.hpp>

namespace how {
namespace model {

bool SegmentComparator::operator()(const types::segment_t &s1,
                                   const types::segment_t &s2) const {
  PointComparator pointComparator;
  types::point_t centroid1;
  types::point_t centroid2;
  bg::centroid(s1, centroid1);
  bg::centroid(s2, centroid2);
  return pointComparator(centroid1, centroid2);
}
} // namespace model
} // namespace how
