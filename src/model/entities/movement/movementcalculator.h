#ifndef MOVEMENTCALCULATOR_H
#define MOVEMENTCALCULATOR_H

#include "../../delaunaygraphtypes.h"
#include "../graphentity.h"
#include "./graphmovement.h"

namespace how {
namespace model {

GraphMovement *
calculateMovement(const types::delaunay_graph_t *graphPtr, GraphEntity *movingEntity,
             types::delaunay_graph_vertex_index_t destionationVertexIndex);

} // namespace model
} // namespace how

#endif // MOVEMENTCALCULATOR_H
