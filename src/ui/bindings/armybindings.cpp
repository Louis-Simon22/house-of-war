#include "armybindings.h"

namespace how {
namespace ui {

ArmyBindings::ArmyBindings() {}

void ArmyBindings::onArmyItemSelected(ArmyItem *armyItem) {
  this->armyItem = armyItem;
  this->updateBindings();
}

bool ArmyBindings::isBound() const { return this->armyItem; }

types::carac_t ArmyBindings::getSize() const { return this->armyItem ? 20 : 0; }

} // namespace ui
} // namespace how
