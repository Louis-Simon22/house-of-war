#include "graphentity.h"

namespace how {
namespace model {
GraphEntity::GraphEntity(types::point_t position,
                         types::delaunay_graph_vertex_index_t currentVertex)
    : Entity(position), currentVertexIndex(currentVertex) {}

types::delaunay_graph_vertex_index_t
GraphEntity::getCurrentVertexIndex() const {
  return this->currentVertexIndex;
}

void GraphEntity::setCurrentVertex(
    types::delaunay_graph_vertex_index_t currentVertexIndex) {
  this->currentVertexIndex = currentVertexIndex;
}
} // namespace model
} // namespace how
