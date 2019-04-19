#ifndef GRAPHMOVEMENT_H
#define GRAPHMOVEMENT_H

#include "../../graphtypes.h"
#include "../entitychange.h"
#include "../graphentity.h"

namespace how {
namespace model {
class GraphMovement : public EntityChange {
public:
  GraphMovement(const types::graph_t *const delaunayGraph,
                GraphEntity *const entity,
                std::vector<types::graph_vertex_desc_t> destinations);
  ~GraphMovement() override;

private:
  const types::graph_t *const delaunayGraph;
  GraphEntity *const entity;
  std::vector<types::graph_vertex_desc_t> destinations;
  std::size_t currentDestinationIndex;

public:
  bool progress(float deltaTime) override;
  void destinationReached() override;
};
} // namespace model
} // namespace how

#endif // GRAPHMOVEMENT_H
