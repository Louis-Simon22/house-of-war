#include "charactergenerator.h"

namespace how {
namespace model {

CharacterData *generateCharacters() {
  auto characters = std::vector<Character>();
  types::delaunay_graph_vertex_index_t *currentVertex1 =
      new types::delaunay_graph_vertex_index_t;
  *currentVertex1 = 10;
  characters.push_back(Character(currentVertex1));
  types::delaunay_graph_vertex_index_t *currentVertex2 =
      new types::delaunay_graph_vertex_index_t;
  *currentVertex2 = 5;
  characters.push_back(Character(currentVertex2));
  return new CharacterData(characters);
}

} // namespace model
} // namespace how
