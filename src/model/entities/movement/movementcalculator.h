#ifndef MOVEMENTCALCULATOR_H
#define MOVEMENTCALCULATOR_H

#include "../../graphtypes.h"
#include "../graphentity.h"
#include "./graphmovement.h"

namespace how {
namespace model {

GraphMovement *
calculateMovement(const types::graph_t *graphPtr,
                  GraphEntity *movingEntity,
                  types::graph_vertex_desc_t destionationVertexIndex);

} // namespace model
} // namespace how

#endif // MOVEMENTCALCULATOR_H
