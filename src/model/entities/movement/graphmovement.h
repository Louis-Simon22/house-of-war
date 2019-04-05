#ifndef GRAPHMOVEMENT_H
#define GRAPHMOVEMENT_H

#include <boost/signals2.hpp>

#include "../../delaunaygraphtypes.h"
#include "../entitychange.h"
#include "../graphentity.h"

namespace how {
namespace model {
namespace {
namespace bs2 = ::boost::signals2;
}
class GraphMovement : public EntityChange {
public:
  GraphMovement(const types::delaunay_graph_t *const delaunayGraph,
                GraphEntity *const entity,
                std::vector<types::delaunay_graph_vertex_index_t> destinations);
  ~GraphMovement() override;

private:
  const types::delaunay_graph_t *const delaunayGraph;
  GraphEntity *const entity;
  std::vector<types::delaunay_graph_vertex_index_t> destinations;
  std::size_t currentDestination;

public:
  bs2::signal<void (int modelIndex)> changeSignal;
  bool progress(float deltaTime) override;
  void destinationReached() override;
};
} // namespace model
} // namespace how

#endif // GRAPHMOVEMENT_H
