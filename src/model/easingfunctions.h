#ifndef EASINGFUNCTIONS_H
#define EASINGFUNCTIONS_H

#include <boost/math/special_functions/pow.hpp>

#include "./modeltypes.h"

namespace how {
namespace model {
namespace {
using fpt_t = types::characteristics_t;
namespace bm = ::boost::math;
} // namespace

inline fpt_t normalize(fpt_t value, fpt_t min, fpt_t max) {
  return (value - min) * (1 / (max - min));
}

inline fpt_t flip(fpt_t value) { return 1 - value; }

template <unsigned long power> inline fpt_t smoothStart(fpt_t value) {
  return bm::pow<power, fpt_t>(value);
}

template <unsigned long power> inline fpt_t smoothEnd(fpt_t value) {
  return flip(bm::pow<power, fpt_t>(flip(value)));
}

} // namespace model
} // namespace how
#endif // EASINGFUNCTIONS_H
