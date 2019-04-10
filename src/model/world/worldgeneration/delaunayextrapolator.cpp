#include "delaunayextrapolator.h"

#include "../../segmentcomparator.h"

namespace how {
namespace model {

// Potential replacement https://github.com/delfrrr/delaunator-cpp
std::tuple<types::delaunay_graph_t, std::vector<DelaunayEdge>,
           std::vector<types::segment_t>>
extrapolateDelaunayTriangulation(std::vector<VoronoiCell> voronoiCells) {
  auto delaunayGraph = types::delaunay_graph_t();
  auto cellsBySegment =
      std::map<types::segment_t, types::delaunay_graph_vertex_desc_t,
               SegmentComparator>();
  auto delaunayEdges = std::vector<DelaunayEdge>();
  auto pathSegmentsSet = std::set<types::segment_t, SegmentComparator>();

  for (const auto &voronoiCell : voronoiCells) {
    auto vertex = ::boost::add_vertex(voronoiCell, delaunayGraph);
    for (const auto &segment : voronoiCell.outlineSegments) {
      const auto &foundIt = cellsBySegment.find(segment);
      if (foundIt == cellsBySegment.end()) {
        cellsBySegment[segment] = vertex;
      } else {
        const auto &found = *foundIt;
        const auto &foundVertix = found.second;
        auto delaunayEdge1 =
            DelaunayEdge(types::segment_t(delaunayGraph[vertex].centroid,
                                          delaunayGraph[foundVertix].centroid));
        auto delaunayEdge2 =
            DelaunayEdge(types::segment_t(delaunayGraph[foundVertix].centroid,
                                          delaunayGraph[vertex].centroid));
        ::boost::add_edge(vertex, foundVertix, delaunayEdge1, delaunayGraph);
        ::boost::add_edge(foundVertix, vertex, delaunayEdge2, delaunayGraph);
        delaunayEdges.push_back(delaunayEdge1);
        delaunayEdges.push_back(delaunayEdge2);
        pathSegmentsSet.insert(delaunayEdge1.segment);
      }
    }
  }

  return std::tuple<types::delaunay_graph_t, std::vector<DelaunayEdge>,
                    std::vector<types::segment_t>>(
      delaunayGraph, delaunayEdges,
      std::vector<types::segment_t>(pathSegmentsSet.begin(),
                                    pathSegmentsSet.end()));
}
} // namespace model
} // namespace how
