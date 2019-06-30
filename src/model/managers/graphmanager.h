#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include <vector>

#include "../graphtypes.h"

namespace how {
namespace model {
class GraphManager {
public:
  GraphManager(types::graph_t graph, types::box_t bounds);

public:
  const types::graph_t &getGraph() const;
  const types::box_t &getBounds() const;
  const std::vector<types::segment_t> &getVoronoiSegments() const;
  const std::vector<types::segment_t> &getDelaunaySegments() const;
  std::vector<types::point_t>
  getDestinationsBetween(types::graph_vertex_desc_t sourceVertexDesc,
                         types::graph_vertex_desc_t destinationVertexDesc);

private:
  types::graph_t graph;
  types::box_t bounds;
  std::vector<types::segment_t> voronoiSegments;
  std::vector<types::segment_t> delaunaySegments;
};
} // namespace model
} // namespace how

#endif // GRAPHMANAGER_H
