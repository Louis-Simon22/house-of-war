#ifndef DELAUNAYEXTRAPOLATOR_H
#define DELAUNAYEXTRAPOLATOR_H

#include "../graphtypes.h"

namespace how {
namespace model {

std::pair<types::graph_t, types::spatial_index_tree_t>
createGraphFromVoronoiCellsAndComputeDelaunayTriangulation(
    std::vector<std::shared_ptr<VoronoiCell>> voronoiCells);

} // namespace model
} // namespace how

#endif // DELAUNAYEXTRAPOLATOR_H
