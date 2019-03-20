#ifndef MOVEMENTWEIGHTCALCULATOR_H
#define MOVEMENTWEIGHTCALCULATOR_H

#include "../../modeltypes.h"
#include "../../world/delaunayedge.h"

namespace how {
namespace model {

class MovementWeightCalculator {
public:
  static types::coordinate_fpt_t calculateEdgeWeight(DelaunayEdge edge);
};

} // namespace model
} // namespace how

#endif // MOVEMENTWEIGHTCALCULATOR_H
