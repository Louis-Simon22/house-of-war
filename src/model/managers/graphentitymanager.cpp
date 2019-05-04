#include "graphentitymanager.h"

namespace how {
namespace model {

GraphEntityManager::GraphEntityManager(std::vector<Character> characters,
                                       std::vector<Army> armies)
    : characters(characters), armies(armies) {}

std::vector<Character> &GraphEntityManager::getCharacters() {
  return this->characters;
}

std::vector<Army> &GraphEntityManager::getArmies() { return this->armies; }

} // namespace model
} // namespace how
