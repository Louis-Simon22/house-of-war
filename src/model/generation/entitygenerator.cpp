#include "entitygenerator.h"

namespace how {
namespace model {

std::vector<Character>
generateCharacters(const types::graph_t *delaunayGraphPtr) {
  const auto &delaunayGraph = *delaunayGraphPtr;
  auto characters = std::vector<Character>();
  types::graph_vertex_desc_t currentVertex = 35;
  characters.emplace_back(delaunayGraph[currentVertex].getCentroid(),
                          currentVertex);
  currentVertex = 15;
  characters.emplace_back(delaunayGraph[currentVertex].getCentroid(),
                          currentVertex);
  return characters;
}

std::vector<Army> generateArmies(const types::graph_t *delaunayGraphPtr) {
  const auto &delaunayGraph = *delaunayGraphPtr;
  auto armies = std::vector<Army>();
  types::graph_vertex_desc_t currentVertex = 30;
  armies.emplace_back(delaunayGraph[currentVertex].getCentroid(),
                      currentVertex);
  currentVertex = 10;
  armies.emplace_back(delaunayGraph[currentVertex].getCentroid(),
                      currentVertex);
  return armies;
}

} // namespace model
} // namespace how
