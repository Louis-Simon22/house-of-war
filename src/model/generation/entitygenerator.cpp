#include "entitygenerator.h"

namespace how {
namespace model {

std::vector<std::shared_ptr<Character>> generateCharacters(const types::graph_t &delaunayGraph) {
  auto characters = std::vector<std::shared_ptr<Character>>();
  characters.emplace_back(new Character(delaunayGraph[3]->getPosition()));
  characters.emplace_back(new Character(delaunayGraph[6]->getPosition()));
  return characters;
}

std::vector<std::shared_ptr<Army>> generateArmies(const types::graph_t &delaunayGraph) {
  auto armies = std::vector<std::shared_ptr<Army>>();
  armies.emplace_back(new Army(delaunayGraph[9]->getPosition()));
  armies.emplace_back(new Army(delaunayGraph[30]->getPosition()));
  return armies;
}

} // namespace model
} // namespace how
