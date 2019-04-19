#include "worlddata.h"

#include <iostream>

namespace how {
namespace model {

WorldData::WorldData(types::box_t bounds,
                     std::vector<types::segment_t> uniqueVoronoiSegments,
                     std::vector<types::segment_t> uniqueDelaunaySegments,
                     types::graph_t graph)
    : graph(graph), bounds(bounds),
      uniqueVoronoiSegments(uniqueVoronoiSegments),
      uniqueDelaunaySegments(uniqueDelaunaySegments), polygonIndexTree() {
  for (types::graph_vertex_desc_t i = 0; i < ::boost::num_vertices(this->graph);
       i++) {
    this->polygonIndexTree.insert(std::make_pair(graph[i].envelope, i));
  }
}

const types::box_t &WorldData::getBounds() const { return this->bounds; }

const std::vector<types::segment_t> *
WorldData::getUniqueVoronoiSegments() const {
  return &this->uniqueVoronoiSegments;
}

const std::vector<types::segment_t> *
WorldData::getUniqueDelaunaySegments() const {
  return &this->uniqueDelaunaySegments;
}

const types::graph_t *WorldData::getGraph() const { return &this->graph; }

std::size_t WorldData::getVoronoiCellCount() const {
  return ::boost::num_vertices(this->graph);
}

const VoronoiCell *
WorldData::getVoronoiCellByDesc(types::graph_vertex_desc_t vertexDesc) const {
  return &graph[vertexDesc];
}

const types::polygon_index_tree_t *WorldData::getPolygonIndexTree() const {
  return &this->polygonIndexTree;
}

} // namespace model
} // namespace how
