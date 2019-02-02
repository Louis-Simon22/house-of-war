#include "worlddata.h"

namespace how {
namespace model {

WorldData::WorldData(types::box_t bounds, std::vector<types::point_t> points,
                     std::vector<types::segment_t> uniqueVoronoiSegments,
                     std::vector<types::segment_t> uniqueDelaunaySegments,
                     std::vector<VoronoiCell> voronoiCells,
                     std::vector<DelaunayEdge> delaunayEdges,
                     types::delaunay_graph_t graph)
    : bounds(bounds), cellCentroids(points),
      uniqueVoronoiSegments(uniqueVoronoiSegments),
      uniqueDelaunaySegments(uniqueDelaunaySegments),
      voronoiCells(voronoiCells), delaunayEdges(delaunayEdges), graph(graph) {}

const std::vector<types::point_t> *WorldData::getCellCentroids() const {
  return &this->cellCentroids;
}

const types::box_t *WorldData::getBounds() const { return &this->bounds; }

const std::vector<types::segment_t> *
WorldData::getUniqueVoronoiSegments() const {
  return &this->uniqueVoronoiSegments;
}

const std::vector<types::segment_t> *
WorldData::getUniqueDelaunaySegments() const {
  return &this->uniqueDelaunaySegments;
}

const std::vector<VoronoiCell> *WorldData::getVoronoiCells() const {
  return &this->voronoiCells;
}

const std::vector<DelaunayEdge> *WorldData::getDelaunayEdges() const {
  return &this->delaunayEdges;
}

const types::delaunay_graph_t *WorldData::getGraph() const {
  return &this->graph;
}

} // namespace model
} // namespace how
