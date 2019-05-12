#ifndef WorldManager_H
#define WorldManager_H

#include <memory>
#include <vector>

#include "../entities/voronoicell.h"
#include "../graphtypes.h"
#include "../modeltypes.h"

namespace how {
namespace model {

class WorldManager {
public:
  WorldManager(types::box_t bounds,
               std::vector<types::segment_t> outlineSegments,
               std::vector<types::segment_t> pathSegments,
               types::graph_t graph);

  const types::box_t &getBounds() const;
  const std::vector<types::segment_t> &getUniqueVoronoiSegments() const;
  const std::vector<types::segment_t> &getUniqueDelaunaySegments() const;
  const types::graph_t &getGraph() const;
  const std::pair<const types::graph_vertex_iterator_t,
                  const types::graph_vertex_iterator_t>
  getVertexIterators() const;
  VoronoiCell &getVoronoiCellByDesc(types::graph_vertex_desc_t vertexDesc);

private:
  types::graph_t graph;
  types::box_t bounds;
  std::vector<types::segment_t> uniqueVoronoiSegments;
  std::vector<types::segment_t> uniqueDelaunaySegments;
  types::polygon_index_tree_t polygonIndexTree;
};
} // namespace model
} // namespace how
#endif // WorldManager_H
