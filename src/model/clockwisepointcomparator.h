#ifndef POINTCOMPARATOR_H
#define POINTCOMPARATOR_H

#include "./modeltypes.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}
class ClockwisePointComparator {
public:
  ClockwisePointComparator(types::point_t pivot);

public:
  bool operator()(const types::point_t &p1, const types::point_t &p2) const;

private:
  types::point_t pivot;
};
} // namespace model
} // namespace how
#endif // POINTCOMPARATOR_H
