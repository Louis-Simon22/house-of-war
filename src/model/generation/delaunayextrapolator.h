#ifndef DELAUNAYEXTRAPOLATOR_H
#define DELAUNAYEXTRAPOLATOR_H

#include "../graphtypes.h"

namespace how {
namespace model {

types::graph_t createGraphFromVoronoiCellsAndComputeDelaunayTriangulation(
    std::vector<std::shared_ptr<Tile>> tiles);

} // namespace model
} // namespace how

#endif // DELAUNAYEXTRAPOLATOR_H
