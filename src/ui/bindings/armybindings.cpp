#include "armybindings.h"

namespace how {
namespace ui {

ArmyBindings::ArmyBindings() : army(nullptr) {}

ArmyBindings::~ArmyBindings() {}

void ArmyBindings::bindArmy(model::Army *army) {
  this->army = army;
  this->bindEntity(army);
}

types::carac_t ArmyBindings::getSize() const { return this->army ? 20 : 0; }

} // namespace ui
} // namespace how
