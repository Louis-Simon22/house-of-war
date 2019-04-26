#ifndef MOVEMENTCALCULATOR_H
#define MOVEMENTCALCULATOR_H

#include "../entities/graphentity.h"
#include "../entities/graphentitypositionchange.h"
#include "../graphtypes.h"

namespace how {
namespace model {

GraphEntityPositionChange *
graphEntityPathfinding(const types::graph_t *graphPtr, GraphEntity &movingEntity,
                  types::graph_vertex_desc_t destinationVertexIndex);

} // namespace model
} // namespace how

#endif // MOVEMENTCALCULATOR_H
