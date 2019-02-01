#ifndef DELAUNAYEXTRAPOLATOR_H
#define DELAUNAYEXTRAPOLATOR_H

#include "../../graphtypes.h"
#include "../../modeltypes.h"
#include "../voronoicell.h"

namespace how {
namespace model {

class DelaunayExtrapolator {
public:
  DelaunayExtrapolator();

  types::delaunay_graph_t
  extrapolateDelaunayTriangulation(std::vector<VoronoiCell> voronoiCells);

private:
  DelaunayEdge delaunayEdgeFromVertices(types::delaunay_graph_vertex_t v1,
                                        types::delaunay_graph_vertex_t v2,
                                        types::delaunay_graph_t g);
};
} // namespace model
} // namespace how

#endif // DELAUNAYEXTRAPOLATOR_H
