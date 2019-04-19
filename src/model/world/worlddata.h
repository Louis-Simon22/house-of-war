#ifndef WORLDDATA_H
#define WORLDDATA_H

#include <memory>
#include <vector>

#include "../graphtypes.h"
#include "../modeltypes.h"
#include "./voronoicell.h"

namespace how {
namespace model {

class WorldData {
public:
  WorldData(types::box_t bounds, std::vector<types::segment_t> outlineSegments,
            std::vector<types::segment_t> pathSegments,
            types::graph_t graph);

  const types::box_t &getBounds() const;
  const std::vector<types::segment_t> *getUniqueVoronoiSegments() const;
  const std::vector<types::segment_t> *getUniqueDelaunaySegments() const;
  const types::graph_t *getGraph() const;
  std::size_t getVoronoiCellCount() const;
  const VoronoiCell *
  getVoronoiCellByDesc(types::graph_vertex_desc_t vertexDesc) const;
  const types::polygon_index_tree_t * getPolygonIndexTree() const;

private:
  types::graph_t graph;
  types::box_t bounds;
  std::vector<types::segment_t> uniqueVoronoiSegments;
  std::vector<types::segment_t> uniqueDelaunaySegments;
  types::polygon_index_tree_t polygonIndexTree;
};
} // namespace model
} // namespace how
#endif // WORLDDATA_H
