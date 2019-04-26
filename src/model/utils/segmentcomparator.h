#ifndef SEGMENTCOMPARATOR_H
#define SEGMENTCOMPARATOR_H

#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}
class SegmentComparator {
public:
  SegmentComparator() {}

  bool operator()(const types::segment_t &s1, const types::segment_t &s2) const;
};
} // namespace model
} // namespace how
#endif // POINTCOMPARATOR_H
