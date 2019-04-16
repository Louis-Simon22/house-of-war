#include "easingfunctions.h"

#include <math.h>

namespace how {
namespace model {

fpt_t normalize(fpt_t value, fpt_t min, fpt_t max) {
  return (value - min) / (max - min);
}

fpt_t flip(fpt_t value) { return 1 - value; }

fpt_t smoothStart(fpt_t value, fpt_t power) { return pow(value, power); }

fpt_t smoothEnd(fpt_t value, fpt_t power) {
  return flip(pow(flip(value), power));
}

} // namespace model
} // namespace how
