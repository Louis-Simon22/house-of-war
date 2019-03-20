#include "graphmovement.h"

namespace how {
namespace model {
GraphMovement::GraphMovement(const types::delaunay_graph_t *const delaunayGraph)
    : EntityMovement(), delaunayGraph(delaunayGraph) {}

GraphMovement::~GraphMovement() {}

bool GraphMovement::progress(float deltaTime) { return true; }

void GraphMovement::destinationReached() {}
} // namespace model
} // namespace how
