#include "character.h"

namespace how {
namespace model {

Character::Character(types::point_t initialPosition)
    : GraphEntity(Layers::CHARACTERS, initialPosition) {}

Character::~Character() {}

bool Character::isTargetable() const { return false; }

bool Character::isSelectable() const { return true; }

bool Character::isWithinSelectionArea(types::coordinate_t posX,
                                      types::coordinate_t posY) const {
  return true;
}

} // namespace model
} // namespace how
