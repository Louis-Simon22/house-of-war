#include "charactergenerator.h"

namespace how {
namespace model {

CharacterData *
generateCharacters(const types::delaunay_graph_t *delaunayGraphPtr) {
  const auto &delaunayGraph = *delaunayGraphPtr;
  auto characters = std::vector<Character>();
  types::delaunay_graph_vertex_desc_t currentVertex = 27;
  characters.emplace_back(delaunayGraph[currentVertex].centroid, currentVertex);
  currentVertex = 46;
  characters.emplace_back(delaunayGraph[currentVertex].centroid, currentVertex);
  return new CharacterData(characters);
}

} // namespace model
} // namespace how
