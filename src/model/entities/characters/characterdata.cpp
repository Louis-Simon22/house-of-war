#include "characterdata.h"

namespace how {
namespace model {
CharacterData::CharacterData(std::vector<Character> characters)
    : characters(characters) {}

const std::vector<Character> *CharacterData::getCharacters() const {
  return &this->characters;
}

Character *CharacterData::getCharacter(std::size_t index) {
  return &this->characters[index];
}
} // namespace model
} // namespace how
