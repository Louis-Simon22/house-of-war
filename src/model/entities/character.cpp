#include "character.h"

namespace how {
namespace model {

Character::Character(types::point_t initialPosition)
    : GraphEntity(Layers::CHARACTERS_LAYER, initialPosition) {}

Character::~Character() {}

types::coordinate_t Character::getWidth() const { return 10; }

types::coordinate_t Character::getHeight() const { return 10; }

bool Character::isTargetable() const { return false; }

bool Character::isSelectable() const { return true; }

} // namespace model
} // namespace how
