#ifndef CHARACTER_H
#define CHARACTER_H

#include "../modeltypes.h"
#include "../graphtypes.h"
#include "./graphentity.h"

namespace how {
namespace model {
class Character : public GraphEntity {
public:
  Character(types::point_t initialPosition,
            types::graph_vertex_desc_t currentVertexIndex);
  ~Character() override;
};
} // namespace model
} // namespace how
#endif // CHARACTER_H
