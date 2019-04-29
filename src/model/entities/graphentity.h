#ifndef GRAPHENTITY_H
#define GRAPHENTITY_H

#include "../graphtypes.h"
#include "./entity.h"
#include "./voronoicell.h"

namespace how {
namespace model {
class GraphEntity : public Entity {
public:
  GraphEntity(types::point_t position,
              types::graph_vertex_desc_t currentVertexDesc);
  virtual ~GraphEntity();

public:
  const types::point_t &getPosition() const;
  void setPosition(types::point_t position);
  types::graph_vertex_desc_t getCurrentVertexDesc() const;
  void setCurrentVertexDesc(const types::graph_vertex_desc_t currentVertexDesc);

private:
  types::point_t position;
  types::graph_vertex_desc_t currentVertexDesc;
};
} // namespace model
} // namespace how

#endif // GRAPHENTITY_H
