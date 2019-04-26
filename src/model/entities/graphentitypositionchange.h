#ifndef GRAPHMOVEMENT_H
#define GRAPHMOVEMENT_H

#include "../graphtypes.h"
#include "./entitychange.h"
#include "./graphentity.h"

namespace how {
namespace model {
class GraphEntityPositionChange : public EntityChange {
public:
  GraphEntityPositionChange(
      const types::graph_t *const delaunayGraph, GraphEntity &entity,
      std::vector<types::graph_vertex_desc_t> destinations);
  ~GraphEntityPositionChange() override;

public:
  bool progress(float deltaTime) override;
  void destinationReached() override;

private:
  const types::graph_t *delaunayGraph;
  GraphEntity &entity;
  std::vector<types::graph_vertex_desc_t> destinations;
  std::size_t currentDestinationIndex;
};
} // namespace model
} // namespace how

#endif // GRAPHMOVEMENT_H
