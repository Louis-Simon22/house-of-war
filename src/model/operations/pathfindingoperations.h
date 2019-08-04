#ifndef MOVEMENTCALCULATOR_H
#define MOVEMENTCALCULATOR_H

#include "../graphtypes.h"

namespace how {
namespace model {

std::vector<types::point_t>
graphEntityPathfinding(types::graph_vertex_desc_t sourceVertexDesc,
                       types::graph_vertex_desc_t destinationVertexDesc,
                       const types::graph_t &graph);

} // namespace model
} // namespace how

#endif // MOVEMENTCALCULATOR_H
