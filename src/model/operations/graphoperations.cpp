#include "graphoperations.h"

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/strategies/strategies.hpp>

#include "../utils/segmentcomparator.h"

namespace how {
namespace model {

std::vector<types::segment_t>
extractUniqueVoronoiSegments(const types::graph_t &graph) {
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
  return std::vector<types::segment_t>(uniqueVoronoiSegmentsSet.begin(),
                                       uniqueVoronoiSegmentsSet.end());
}

std::vector<types::segment_t>
extractUniqueDelaunaySegments(const types::graph_t &graph) {
    types::graph_edge_iterator_t edgeItBegin, edgeItEnd;
    std::tie(edgeItBegin, edgeItEnd) = ::boost::edges(graph);
    auto uniqueDelaunaySegmentsSet =
        std::set<types::segment_t, SegmentComparator>();
    for (auto edgeIt = edgeItBegin; edgeIt != edgeItEnd; edgeIt++) {
      auto edgeDesc = *edgeIt;
      auto &delaunayEdgePtr = graph[edgeDesc];
      const auto &edgeSegment = delaunayEdgePtr->getSegment();
      uniqueDelaunaySegmentsSet.insert(edgeSegment);
    }
    return std::vector<types::segment_t>(uniqueDelaunaySegmentsSet.begin(),
                                         uniqueDelaunaySegmentsSet.end());
}

} // namespace model
} // namespace how
