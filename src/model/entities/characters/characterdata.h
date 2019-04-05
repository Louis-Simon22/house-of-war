#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H

#include <memory>

#include "./character.h"

namespace how {
namespace model {
class CharacterData {
public:
  CharacterData(std::vector<Character> characters);

  const std::vector<Character> *getCharacters() const;
  Character *getCharacter(std::size_t index);

private:
  std::vector<Character> characters;
};
} // namespace model
} // namespace how

#endif // CHARACTERDATA_H
