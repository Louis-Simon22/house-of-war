#ifndef DELAUNAYEXTRAPOLATOR_H
#define DELAUNAYEXTRAPOLATOR_H

#include "../graphtypes.h"

namespace how {
namespace model {

std::tuple<types::graph_t, std::vector<types::segment_t>>
extractDelaunayTriangulation(std::vector<VoronoiCell> voronoiCells);

} // namespace model
} // namespace how

#endif // DELAUNAYEXTRAPOLATOR_H