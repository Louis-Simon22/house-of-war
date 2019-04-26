#include "graphentity.h"

namespace how {
namespace model {

GraphEntity::GraphEntity(types::point_t position,
                         types::graph_vertex_desc_t currentVertexDesc)
    : Entity(), position(position), currentVertexDesc(currentVertexDesc) {}

GraphEntity::~GraphEntity() {}

const types::point_t &GraphEntity::getPosition() const {
  return this->position;
}

void GraphEntity::setPosition(types::point_t position) {
  this->position = position;
}

types::graph_vertex_desc_t GraphEntity::getCurrentVertexDesc() const {
  return this->currentVertexDesc;
}

void GraphEntity::setCurrentVertexDesc(
    types::graph_vertex_desc_t currentVertexDesc) {
  this->currentVertexDesc = currentVertexDesc;
}

} // namespace model
} // namespace how
