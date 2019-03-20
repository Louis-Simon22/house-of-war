#ifndef DELAUNAYEXTRAPOLATOR_H
#define DELAUNAYEXTRAPOLATOR_H

#include "../../delaunaygraphtypes.h"
#include "../../modeltypes.h"
#include "../voronoicell.h"

namespace how {
namespace model {

class DelaunayExtrapolator {
public:
  static std::tuple<types::delaunay_graph_t, std::vector<DelaunayEdge>,
                    std::vector<types::segment_t>>
  extrapolateDelaunayTriangulation(std::vector<VoronoiCell> voronoiCells);

private:
  static DelaunayEdge
  delaunayEdgeFromVertices(types::delaunay_graph_vertex_index_t v1,
                           types::delaunay_graph_vertex_index_t v2,
                           types::delaunay_graph_t g);
};
} // namespace model
} // namespace how

#endif // DELAUNAYEXTRAPOLATOR_H
