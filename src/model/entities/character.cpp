#include "character.h"

namespace how {
namespace model {

Character::Character(types::point_t initialPosition)
    : InteractiveEntity(Layers::CHARACTERS, initialPosition) {}

Character::~Character() {}

bool Character::isTargetable() const { return false; }

bool Character::isSelectable() const { return true; }

} // namespace model
} // namespace how
