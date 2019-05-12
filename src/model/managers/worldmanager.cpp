#include "worldmanager.h"

namespace how {
namespace model {

WorldManager::WorldManager(types::box_t bounds,
                           std::vector<types::segment_t> uniqueVoronoiSegments,
                           std::vector<types::segment_t> uniqueDelaunaySegments,
                           types::graph_t graph)
    : graph(graph), bounds(bounds),
      uniqueVoronoiSegments(uniqueVoronoiSegments),
      uniqueDelaunaySegments(uniqueDelaunaySegments), polygonIndexTree() {
  for (types::graph_vertex_desc_t i = 0; i < ::boost::num_vertices(this->graph);
       i++) {
    this->polygonIndexTree.insert(std::make_pair(graph[i].getEnvelope(), i));
  }
}

const types::box_t &WorldManager::getBounds() const { return this->bounds; }

const std::vector<types::segment_t> &
WorldManager::getUniqueVoronoiSegments() const {
  return this->uniqueVoronoiSegments;
}

const std::vector<types::segment_t> &
WorldManager::getUniqueDelaunaySegments() const {
  return this->uniqueDelaunaySegments;
}

const types::graph_t &WorldManager::getGraph() const { return this->graph; }

const std::pair<const types::graph_vertex_iterator_t,
                const types::graph_vertex_iterator_t>
ModelManager::getVertexIterators() const {
  return ::boost::vertices(this->getWorldManagerPtr()->getGraph());
}

VoronoiCell &
WorldManager::getVoronoiCellByDesc(types::graph_vertex_desc_t vertexDesc) {
  return graph[vertexDesc];
}

} // namespace model
} // namespace how
