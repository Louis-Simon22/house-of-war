#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "./army.h"
#include "./character.h"

namespace how {
namespace model {
class Player {
public:
  Player();

public:
  void addArmy(Army *army);
  std::vector<std::shared_ptr<Army>> &getArmyPtrs();

private:
  std::vector<std::shared_ptr<Army>> armyPtrs;
};
} // namespace model
} // namespace how

#endif // PLAYER_H
