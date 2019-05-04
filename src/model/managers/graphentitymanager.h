#ifndef GRAPHENTITYMANAGER_H
#define GRAPHENTITYMANAGER_H

#include <vector>

#include "../entities/army.h"
#include "../entities/character.h"

namespace how {
namespace model {
// TODO no need for this anymore? Group everything in a "model" object
class GraphEntityManager {
public:
  GraphEntityManager(std::vector<Character> characters,
                     std::vector<Army> armies);

public:
  std::vector<Character> &getCharacters();
  std::vector<Army> &getArmies();

private:
  std::vector<Character> characters;
  std::vector<Army> armies;
};
} // namespace model
} // namespace how

#endif // GRAPHENTITYMANAGER_H
