#include "entitygenerator.h"

namespace how {
namespace model {

std::vector<Character> generateCharacters(const types::graph_t &delaunayGraph) {
  auto characters = std::vector<Character>();
  characters.emplace_back(delaunayGraph[3].getCenter());
  characters.emplace_back(delaunayGraph[6].getCenter());
  return characters;
}

std::vector<Army> generateArmies(const types::graph_t &delaunayGraph) {
  auto armies = std::vector<Army>();
  armies.emplace_back(delaunayGraph[9].getCenter());
  armies.emplace_back(delaunayGraph[12].getCenter());
  return armies;
}

} // namespace model
} // namespace how
