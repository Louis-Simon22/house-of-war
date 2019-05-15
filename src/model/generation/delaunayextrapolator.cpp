#include "delaunayextrapolator.h"

#include "../utils/segmentcomparator.h"

namespace how {
namespace model {

// Potential replacement https://github.com/delfrrr/delaunator-cpp
std::tuple<types::graph_t, std::vector<types::segment_t>>
extractDelaunayTriangulation(std::vector<VoronoiCell> voronoiCells) {
  auto delaunayGraph = types::graph_t();
  auto cellsBySegment = std::map<types::segment_t, types::graph_vertex_desc_t,
                                 SegmentComparator>();
  auto pathSegmentsSet = std::set<types::segment_t, SegmentComparator>();

  for (const auto &voronoiCell : voronoiCells) {
    auto vertex = ::boost::add_vertex(voronoiCell, delaunayGraph);
    for (const auto &segment : voronoiCell.getOutlineSegments()) {
      const auto &foundIt = cellsBySegment.find(segment);
      if (foundIt == cellsBySegment.end()) {
        cellsBySegment[segment] = vertex;
      } else {
        const auto &found = *foundIt;
        const auto &foundVertex = found.second;
        auto delaunayEdge1 = DelaunayEdge(
            types::segment_t(delaunayGraph[vertex].getCenter(),
                             delaunayGraph[foundVertex].getCenter()));
        auto delaunayEdge2 = DelaunayEdge(
            types::segment_t(delaunayGraph[foundVertex].getCenter(),
                             delaunayGraph[vertex].getCenter()));
        ::boost::add_edge(vertex, foundVertex, delaunayEdge1, delaunayGraph);
        ::boost::add_edge(foundVertex, vertex, delaunayEdge2, delaunayGraph);
        pathSegmentsSet.insert(delaunayEdge1.getSegment());
      }
    }
  }

  return std::tuple<types::graph_t, std::vector<types::segment_t>>(
      delaunayGraph, std::vector<types::segment_t>(pathSegmentsSet.begin(),
                                                   pathSegmentsSet.end()));
}
} // namespace model
} // namespace how
