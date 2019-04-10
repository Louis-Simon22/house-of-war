#ifndef DELAUNAYEXTRAPOLATOR_H
#define DELAUNAYEXTRAPOLATOR_H

#include "../../delaunaygraphtypes.h"
#include "../voronoicell.h"

namespace how {
namespace model {

std::tuple<types::delaunay_graph_t, std::vector<DelaunayEdge>,
           std::vector<types::segment_t>>
extrapolateDelaunayTriangulation(std::vector<VoronoiCell> voronoiCells);

} // namespace model
} // namespace how

#endif // DELAUNAYEXTRAPOLATOR_H
