#ifndef GRAPHENTITY_H
#define GRAPHENTITY_H

#include "../graphtypes.h"
#include "../world/voronoicell.h"
#include "./entity.h"

namespace how {
namespace model {
class GraphEntity : public Entity {
public:
  GraphEntity(types::point_t position,
              const types::graph_vertex_desc_t currentVertexIndex);

public:
  types::point_t position;

private:
  types::graph_vertex_desc_t currentVertexIndex;

public:
  types::graph_vertex_desc_t getCurrentVertexIndex() const;
  void setCurrentVertex(
      const types::graph_vertex_desc_t currentVertexIndex);
};
} // namespace model
} // namespace how

#endif // GRAPHENTITY_H
