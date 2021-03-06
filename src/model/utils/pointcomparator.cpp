#include "./pointcomparator.h"

#include <cmath>

namespace how {
namespace model {

PointComparator::PointComparator() {}

PointComparator::PointComparator(const types::point_t &p1) : p1(&p1) {}

bool PointComparator::operator()(const types::point_t &p1,
                                 const types::point_t &p2) const {
  const auto &x1 = bg::get<0>(p1);
  const auto &x2 = bg::get<0>(p2);
  if (x1 == x2) {
    const auto &y1 = bg::get<1>(p1);
    const auto &y2 = bg::get<1>(p2);
    return y1 < y2;
  } else {
    return x1 < x2;
  }
}

bool PointComparator::operator()(const types::point_t &p2) const {
  return this->operator()(*this->p1, p2);
}

} // namespace model
} // namespace how
