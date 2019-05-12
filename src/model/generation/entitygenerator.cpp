#include "entitygenerator.h"

namespace how {
namespace model {

std::vector<Character>
generateCharacters(const types::graph_t &delaunayGraph) {
  auto characters = std::vector<Character>();
  types::graph_vertex_desc_t currentVertex = 3;
  characters.emplace_back(delaunayGraph[currentVertex].getCenter(),
                          currentVertex);
  currentVertex = 6;
  characters.emplace_back(delaunayGraph[currentVertex].getCenter(),
                          currentVertex);
  return characters;
}

std::vector<Army> generateArmies(const types::graph_t &delaunayGraph) {
  auto armies = std::vector<Army>();
  types::graph_vertex_desc_t currentVertex = 9;
  armies.emplace_back(delaunayGraph[currentVertex].getCenter(),
                          currentVertex);
  currentVertex = 12;
  armies.emplace_back(delaunayGraph[currentVertex].getCenter(),
                          currentVertex);
  return armies;
}

} // namespace model
} // namespace how
