#include "characterdata.h"

namespace how {
namespace model {
CharacterData::CharacterData(std::vector<Character> characters)
    : characters(characters) {}

const std::vector<Character> *CharacterData::getCharacters() const{
  return &this->characters;
}
} // namespace model
} // namespace how
