#include "movementweightcalculator.h"

namespace how {
namespace model {

types::coordinate_fpt_t
MovementWeightCalculator::calculateEdgeWeight(DelaunayEdge edge) {
  return edge.distance;
}

} // namespace model
} // namespace how
