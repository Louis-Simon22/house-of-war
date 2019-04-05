#ifndef CHARACTER_H
#define CHARACTER_H

#include "../graphentity.h"

namespace how {
namespace model {
class Character : public GraphEntity {
public:
  Character(types::point_t initialPosition, types::delaunay_graph_vertex_index_t currentVertexIndex);
};
} // namespace model
} // namespace how
#endif // CHARACTER_H
