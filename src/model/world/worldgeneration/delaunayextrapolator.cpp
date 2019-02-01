#include "delaunayextrapolator.h"

#include "../../segmentcomparator.h"

namespace how {
namespace model {
DelaunayExtrapolator::DelaunayExtrapolator() {}

types::delaunay_graph_t DelaunayExtrapolator::extrapolateDelaunayTriangulation(
    std::vector<VoronoiCell> voronoiCells) {
  auto delaunayGraph = types::delaunay_graph_t();
  auto cellsBySegment =
      std::map<types::segment_t, types::delaunay_graph_vertex_t,
               SegmentComparator>();

  for (const auto &voronoiCell : voronoiCells) {
    auto vertex = ::boost::add_vertex(voronoiCell, delaunayGraph);
    for (const auto &segment : voronoiCell.segments) {
      const auto &foundIt = cellsBySegment.find(segment);
      if (foundIt == cellsBySegment.end()) {
        cellsBySegment[segment] = vertex;
      } else {
        const auto &found = *foundIt;
        const auto &foundVertix = found.second;
        ::boost::add_edge(
            vertex, foundVertix,
            delaunayEdgeFromVertices(vertex, foundVertix, delaunayGraph),
            delaunayGraph);
        ::boost::add_edge(
            foundVertix, vertex,
            delaunayEdgeFromVertices(vertex, foundVertix, delaunayGraph),
            delaunayGraph);
      }
    }
  }

  return delaunayGraph;
}

DelaunayEdge DelaunayExtrapolator::delaunayEdgeFromVertices(
    types::delaunay_graph_vertex_t v1, types::delaunay_graph_vertex_t v2,
    types::delaunay_graph_t g) {
  return DelaunayEdge(types::segment_t(g[v1].centroid, g[v2].centroid));
}
} // namespace model
} // namespace how
