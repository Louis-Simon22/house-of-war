#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "../characters/army.h"

namespace how {
namespace model {
class Player {
public:
  Player();

public:
  void addArmy(Army *army);
  std::vector<std::shared_ptr<Army>> &getArmyPtrs();

private:
  // TODO create new army from the owned land
  std::vector<std::shared_ptr<Army>> armyPtrs;
  // TODO unique identifier for the player?
};
} // namespace model
} // namespace how

#endif // PLAYER_H
