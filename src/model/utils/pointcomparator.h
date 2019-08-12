#ifndef POINTCOMPARATOR_H
#define POINTCOMPARATOR_H

#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}
class PointComparator {
public:
  PointComparator();
  PointComparator(const types::point_t &p1);

public:
  bool operator()(const types::point_t &p1, const types::point_t &p2) const;
  bool operator()(const types::point_t &p2) const;

private:
  const types::point_t *p1;
};
} // namespace model
} // namespace how
#endif // POINTCOMPARATOR_H
