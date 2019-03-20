#ifndef PROGRESSIVEMOVEMENT_H
#define PROGRESSIVEMOVEMENT_H

#include "../../delaunaygraphtypes.h"
#include "../graphentity.h"
#include "entitymovement.h"

namespace how {
namespace model {
class ProgressiveMovement : public EntityMovement {
public:
  ProgressiveMovement(
      const types::delaunay_graph_t *const delaunayGraph, GraphEntity *entity,
      std::vector<const types::delaunay_graph_vertex_index_t *> destinations);
  ~ProgressiveMovement() override;

private:
  const types::delaunay_graph_t *const delaunayGraph;
  Entity *entity;
  std::vector<const types::delaunay_graph_vertex_index_t *> destinations;
  std::size_t currentDestination;

public:
  bool progress(float deltaTime) override;
  void destinationReached() override;
};
} // namespace model
} // namespace how

#endif // PROGRESSIVEMOVEMENT_H
