#include "character.h"

namespace how {
namespace model {

Character::Character(types::point_t initialPosition,
                     types::graph_vertex_desc_t currentVertex)
    : GraphEntity(initialPosition, currentVertex) {}

Character::~Character() {}

} // namespace model
} // namespace how
