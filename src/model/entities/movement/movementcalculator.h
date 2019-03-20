#ifndef MOVEMENTCALCULATOR_H
#define MOVEMENTCALCULATOR_H

#include "../../delaunaygraphtypes.h"
#include "../entity.h"
#include "../graphentity.h"
#include "./progressivemovement.h"

namespace how {
namespace model {

static ProgressiveMovement moveEntityTo(const types::delaunay_graph_t *graph,
                         GraphEntity moved, GraphEntity destination);

} // namespace model
} // namespace how

#endif // MOVEMENTCALCULATOR_H
