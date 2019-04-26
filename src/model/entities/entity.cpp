#include "entity.h"

namespace how {
namespace model {
Entity::Entity() : uuid(uuids::random_generator()()) {}

Entity::~Entity() {}

const uuids::uuid &Entity::getUuid() const { return this->uuid; }
} // namespace model
} // namespace how
