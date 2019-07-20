#include "player.h"

namespace how {
namespace model {

Player::Player() : armyPtrs() {}

void Player::addArmy(Army *army) {
  this->armyPtrs.push_back(std::shared_ptr<Army>(army));
}

std::vector<std::shared_ptr<Army>> &Player::getArmyPtrs() {
  return this->armyPtrs;
}

} // namespace model
} // namespace how
