#ifndef GRAPHENTITY_H
#define GRAPHENTITY_H

#include "../delaunaygraphtypes.h"
#include "../world/voronoicell.h"
#include "./entity.h"

namespace how {
namespace model {
class GraphEntity : public Entity {
public:
  GraphEntity(types::point_t position,
              const types::delaunay_graph_vertex_index_t currentVertexIndex);

public:
  types::point_t position;

private:
  types::delaunay_graph_vertex_index_t currentVertexIndex;

public:
  types::delaunay_graph_vertex_index_t getCurrentVertexIndex() const;
  void setCurrentVertex(
      const types::delaunay_graph_vertex_index_t currentVertexIndex);
};
} // namespace model
} // namespace how

#endif // GRAPHENTITY_H
