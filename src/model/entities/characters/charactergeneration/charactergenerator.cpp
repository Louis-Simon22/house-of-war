#include "charactergenerator.h"

namespace how {
namespace model {

CharacterData *
generateCharacters(const types::graph_t *delaunayGraphPtr) {
  const auto &delaunayGraph = *delaunayGraphPtr;
  auto characters = std::vector<Character>();
  types::graph_vertex_desc_t currentVertex = 35;
  characters.emplace_back(delaunayGraph[currentVertex].centroid, currentVertex);
  currentVertex = 15;
  characters.emplace_back(delaunayGraph[currentVertex].centroid, currentVertex);
  return new CharacterData(characters);
}

} // namespace model
} // namespace how
