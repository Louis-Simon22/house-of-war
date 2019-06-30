#include "graphmanager.h"

#include <set>

#include "../operations/pathfindingoperations.h"
#include "../utils/segmentcomparator.h"

namespace how {
namespace model {

GraphManager::GraphManager(types::graph_t graph, types::box_t bounds)
    : graph(graph), bounds(bounds), voronoiSegments(), delaunaySegments() {
  types::graph_vertex_iterator_t vertexItBegin, vertexItEnd;
  std::tie(vertexItBegin, vertexItEnd) = ::boost::vertices(graph);
  auto uniqueVoronoiSegmentsSet =
      std::set<types::segment_t, SegmentComparator>();
  for (auto vertexIt = vertexItBegin; vertexIt != vertexItEnd; vertexIt++) {
    auto vertexDesc = *vertexIt;
    auto &tilePtr = graph[vertexDesc];
    const auto &outlineSegments = tilePtr->getOutlineSegments();
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

const types::graph_t &GraphManager::getGraph() const { return this->graph; }

const types::box_t &GraphManager::getBounds() const { return this->bounds; }

const std::vector<types::segment_t> &GraphManager::getVoronoiSegments() const {
  return this->voronoiSegments;
}

const std::vector<types::segment_t> &GraphManager::getDelaunaySegments() const {
  return this->delaunaySegments;
}

std::vector<types::point_t> GraphManager::getDestinationsBetween(
    types::graph_vertex_desc_t sourceVertexDesc,
    types::graph_vertex_desc_t destinationVertexDesc) {
  return graphEntityPathfinding(sourceVertexDesc, destinationVertexDesc,
                                this->graph);
}

} // namespace model
} // namespace how
