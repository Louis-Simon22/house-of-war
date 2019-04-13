#include "worlddata.h"

#include <iostream>

namespace how {
namespace model {

WorldData::WorldData(types::box_t bounds,
                     std::vector<types::segment_t> uniqueVoronoiSegments,
                     std::vector<types::segment_t> uniqueDelaunaySegments,
                     types::delaunay_graph_t graph)
    : bounds(bounds), uniqueVoronoiSegments(uniqueVoronoiSegments),
      uniqueDelaunaySegments(uniqueDelaunaySegments), graph(graph) {}

const types::box_t &WorldData::getBounds() const { return this->bounds; }

const std::vector<types::segment_t> *
WorldData::getUniqueVoronoiSegments() const {
  return &this->uniqueVoronoiSegments;
}

const std::vector<types::segment_t> *
WorldData::getUniqueDelaunaySegments() const {
  return &this->uniqueDelaunaySegments;
}

const types::delaunay_graph_t *WorldData::getGraph() const {
  return &this->graph;
}

std::size_t WorldData::getVoronoiCellCount() const {
  return ::boost::num_vertices(this->graph);
}

const VoronoiCell *WorldData::getVoronoiCellByDesc(
    types::delaunay_graph_vertex_desc_t vertexDesc) const {
  return &graph[vertexDesc];
}

} // namespace model
} // namespace how
