#include "entitygenerator.h"

namespace how {
namespace model {

std::vector<Character>
generateCharacters(const types::graph_t *delaunayGraphPtr) {
  const auto &delaunayGraph = *delaunayGraphPtr;
  auto characters = std::vector<Character>();
  types::graph_vertex_desc_t currentVertex = 35;
  characters.emplace_back(delaunayGraph[currentVertex].getCentroid(), currentVertex);
  currentVertex = 15;
  characters.emplace_back(delaunayGraph[currentVertex].getCentroid(), currentVertex);
  return characters;
}

} // namespace model
} // namespace how
