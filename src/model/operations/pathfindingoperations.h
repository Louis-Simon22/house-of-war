#ifndef MOVEMENTCALCULATOR_H
#define MOVEMENTCALCULATOR_H

#include "../entities/graphentity.h"
#include "../entities/graphentitypositionchange.h"
#include "../graphtypes.h"

namespace how {
namespace model {

GraphEntityPositionChange *
graphEntityPathfinding(GraphEntity &sourceEntity,
                       types::graph_vertex_desc_t destinationVertexDesc,
                       const types::graph_t &graph);

} // namespace model
} // namespace how

#endif // MOVEMENTCALCULATOR_H
