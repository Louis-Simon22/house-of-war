#ifndef GRAPHENTITY_H
#define GRAPHENTITY_H

#include "../world/voronoicell.h"
#include "./entity.h"

namespace how {
namespace model {
class GraphEntity : public Entity {
public:
  GraphEntity(types::point_t position,
              const types::delaunay_graph_vertex_index_t *currentVertexIndex);

private:
  const types::delaunay_graph_vertex_index_t *currentVertexIndex;

public:
  const types::delaunay_graph_vertex_index_t *getCurrentVertexIndex() const;
  void setCurrentVertex(
      const types::delaunay_graph_vertex_index_t *currentVertexIndex);
};
} // namespace model
} // namespace how

#endif // GRAPHENTITY_H
