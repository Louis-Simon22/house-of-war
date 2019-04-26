#include "graphentitymanager.h"

namespace how {
namespace model {
GraphEntityManager::GraphEntityManager(std::vector<Character> characters,
                                       std::vector<Army> armies)
    : characters(characters), armies(armies) {}

const std::vector<Character> &GraphEntityManager::getCharacters() const {
  return this->characters;
}

Character &GraphEntityManager::getCharacter(std::size_t index) {
  return this->characters[index];
}

const std::vector<Army> &GraphEntityManager::getArmies() const {
  return this->armies;
}

Army &GraphEntityManager::getArmy(std::size_t index) {
  return this->armies[index];
}
} // namespace model
} // namespace how
