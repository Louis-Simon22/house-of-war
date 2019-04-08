#include "entity.h"

namespace how {
namespace model {
Entity::Entity() : uuid(uuids::random_generator()())  {}

Entity::~Entity() {}
} // namespace model
} // namespace how
