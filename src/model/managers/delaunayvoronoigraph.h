#ifndef GRAPHENTITYMANAGER_H
#define GRAPHENTITYMANAGER_H

#include <vector>

#include "../entities/entitychange.h"
#include "../graphtypes.h"

namespace how {
namespace model {
class DelaunayVoronoiGraph {
public:
  DelaunayVoronoiGraph(types::graph_t graph,
                       types::spatial_index_tree_t voronoiCellsSpatialIndexTree,
                       types::box_t bounds);

public:
  const types::graph_t &getGraph() const;
  const types::box_t &getBounds() const;
  const types::spatial_index_tree_t &getSpatialIndexTree() const;
  const std::vector<types::segment_t> &getVoronoiSegments() const;
  const std::vector<types::segment_t> &getDelaunaySegments() const;
  std::shared_ptr<::how::model::VoronoiCell>
  getVoronoiCellPtrByDesc(types::graph_vertex_desc_t vertexDesc);
  types::graph_vertex_desc_t
  getVertexDescByPosition(const types::point_t &position) const;
  VoronoiCell *getVoronoiCellByPosition(const types::point_t &position) const;
  std::vector<const VoronoiCell *> getDestinationsBetween(const Entity *source,
                                                    const Entity *destination);

private:
  types::graph_t graph;
  types::box_t bounds;
  types::spatial_index_tree_t voronoiCellsSpatialIndexTree;
  std::vector<types::segment_t> voronoiSegments;
  std::vector<types::segment_t> delaunaySegments;
};
} // namespace model
} // namespace how

#endif // GRAPHENTITYMANAGER_H
