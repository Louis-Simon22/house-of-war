#include "delaunayvoronoigraph.h"

#include <set>

#include "../entities/entitypositionchange.h"
#include "../operations/pathfindingoperations.h"
#include "../operations/polygonindexoperations.h"
#include "../utils/segmentcomparator.h"

namespace how {
namespace model {

DelaunayVoronoiGraph::DelaunayVoronoiGraph(
    types::graph_t graph,
    types::spatial_index_tree_t voronoiCellSpatialIndexTree,
    types::box_t bounds)
    : graph(graph), bounds(bounds),
      voronoiCellsSpatialIndexTree(voronoiCellSpatialIndexTree),
      voronoiSegments(), delaunaySegments() {
  types::graph_vertex_iterator_t vertexItBegin, vertexItEnd;
  std::tie(vertexItBegin, vertexItEnd) = ::boost::vertices(graph);
  auto uniqueVoronoiSegmentsSet =
      std::set<types::segment_t, SegmentComparator>();
  for (auto vertexIt = vertexItBegin; vertexIt != vertexItEnd; vertexIt++) {
    auto vertexDesc = *vertexIt;
    auto &voronoiCellPtr = graph[vertexDesc];
    const auto &outlineSegments = voronoiCellPtr->getOutlineSegments();
    for (const auto &outlineSegment : outlineSegments) {
      uniqueVoronoiSegmentsSet.insert(outlineSegment);
    }
  }
  this->voronoiSegments.insert(this->voronoiSegments.end(),
                               uniqueVoronoiSegmentsSet.begin(),
                               uniqueVoronoiSegmentsSet.end());

  types::graph_edge_iterator_t edgeItBegin, edgeItEnd;
  std::tie(edgeItBegin, edgeItEnd) = ::boost::edges(graph);
  auto uniqueDelaunaySegmentsSet =
      std::set<types::segment_t, SegmentComparator>();
  for (auto edgeIt = edgeItBegin; edgeIt != edgeItEnd; edgeIt++) {
    auto edgeDesc = *edgeIt;
    auto &delaunayEdge = *graph[edgeDesc];
    const auto &edgeSegment = delaunayEdge.getSegment();
    uniqueDelaunaySegmentsSet.insert(edgeSegment);
  }
  this->delaunaySegments.insert(this->delaunaySegments.end(),
                                uniqueDelaunaySegmentsSet.begin(),
                                uniqueDelaunaySegmentsSet.end());
}

const types::graph_t &DelaunayVoronoiGraph::getGraph() const {
  return this->graph;
}

const types::box_t &DelaunayVoronoiGraph::getBounds() const {
  return this->bounds;
}

const types::spatial_index_tree_t &
DelaunayVoronoiGraph::getSpatialIndexTree() const {
  return this->voronoiCellsSpatialIndexTree;
}

const std::vector<types::segment_t> &
DelaunayVoronoiGraph::getVoronoiSegments() const {
  return this->voronoiSegments;
}

const std::vector<types::segment_t> &
DelaunayVoronoiGraph::getDelaunaySegments() const {
  return this->delaunaySegments;
}

std::shared_ptr<VoronoiCell> DelaunayVoronoiGraph::getVoronoiCellPtrByDesc(
    types::graph_vertex_desc_t vertexDesc) {
  return this->graph[vertexDesc];
}

types::graph_vertex_desc_t DelaunayVoronoiGraph::getVertexDescByPosition(
    const types::point_t &position) const {
  return coveredByPoint(position, this->voronoiCellsSpatialIndexTree,
                        this->graph);
}

VoronoiCell *DelaunayVoronoiGraph::getVoronoiCellByPosition(
    const types::point_t &position) const {
  return this->graph[this->getVertexDescByPosition(position)].get();
}

std::vector<const VoronoiCell *>
DelaunayVoronoiGraph::getDestinationsBetween(const Entity *source,
                                             const Entity *destination) {
  const auto sourceVertexDesc =
      this->getVertexDescByPosition(source->getPosition());
  const auto destinationVertexDesc =
      this->getVertexDescByPosition(destination->getPosition());
  return graphEntityPathfinding(sourceVertexDesc, destinationVertexDesc,
                                this->graph);
}

} // namespace model
} // namespace how
