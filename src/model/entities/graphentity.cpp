#include "graphentity.h"

namespace how {
namespace model {
GraphEntity::GraphEntity(
    types::point_t position,
    const types::delaunay_graph_vertex_index_t *currentVertex)
    : Entity(position), currentVertexIndex(currentVertex) {}

const types::delaunay_graph_vertex_index_t *
GraphEntity::getCurrentVertexIndex() const {
  return this->currentVertexIndex;
}

void GraphEntity::setCurrentVertex(
    const types::delaunay_graph_vertex_index_t *currentVertexIndex) {
  this->currentVertexIndex = currentVertexIndex;
}
} // namespace model
} // namespace how
