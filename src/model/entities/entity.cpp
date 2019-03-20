#include "entity.h"

namespace how {
namespace model {
Entity::Entity() {}
Entity::Entity(types::point_t position) : position(position) {}

Entity::~Entity() {}
} // namespace model
} // namespace how
