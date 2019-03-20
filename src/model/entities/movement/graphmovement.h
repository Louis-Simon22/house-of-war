#ifndef GRAPHMOVEMENT_H
#define GRAPHMOVEMENT_H

#include "../../delaunaygraphtypes.h"
#include "entitymovement.h"

namespace how {
namespace model {
class GraphMovement : public EntityMovement {
public:
  GraphMovement(const types::delaunay_graph_t* const delaunayGraph);
  ~GraphMovement() override;

private:
  const types::delaunay_graph_t* const delaunayGraph;

public:
  bool progress(float deltaTime) override;
  void destinationReached() override;
};
} // namespace model
} // namespace how

#endif // GRAPHMOVEMENT_H
