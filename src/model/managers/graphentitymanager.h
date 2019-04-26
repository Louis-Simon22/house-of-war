#ifndef GRAPHENTITYMANAGER_H
#define GRAPHENTITYMANAGER_H

#include <vector>

#include "../entities/army.h"
#include "../entities/character.h"

namespace how {
namespace model {
class GraphEntityManager {
public:
  GraphEntityManager(std::vector<Character> characters,
                     std::vector<Army> armies);

  const std::vector<Character> &getCharacters() const;
  Character &getCharacter(std::size_t index);

  const std::vector<Army> &getArmies() const;
  Army &getArmy(std::size_t index);

private:
  std::vector<Character> characters;
  std::vector<Army> armies;
};
} // namespace model
} // namespace how

#endif // GRAPHENTITYMANAGER_H
