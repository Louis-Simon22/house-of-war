#ifndef DELAUNAYEXTRAPOLATOR_H
#define DELAUNAYEXTRAPOLATOR_H

#include "../../modeltypes.h"
#include "../voronoicell.h"

namespace how {
namespace model {

class DelaunayExtrapolator {
public:
  DelaunayExtrapolator();

  types::delaunayGraph extrapolateDelaunayTriangulation(std::vector<VoronoiCell> voronoiCells);
};
} // namespace model
} // namespace how

#endif // DELAUNAYEXTRAPOLATOR_H
