#include "graphentity.h"

namespace how {
namespace model {
GraphEntity::GraphEntity(types::point_t position,
                         types::graph_vertex_desc_t currentVertex)
    : Entity(), position(position), currentVertexIndex(currentVertex) {}

types::graph_vertex_desc_t
GraphEntity::getCurrentVertexIndex() const {
  return this->currentVertexIndex;
}

void GraphEntity::setCurrentVertex(
    types::graph_vertex_desc_t currentVertexIndex) {
  this->currentVertexIndex = currentVertexIndex;
}
} // namespace model
} // namespace how
