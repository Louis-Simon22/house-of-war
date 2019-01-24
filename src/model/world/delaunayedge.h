#ifndef DELAUNAYEDGE_H
#define DELAUNAYEDGE_H

#include "../modeltypes.h"

namespace how {
namespace model {
struct DelaunayEdge {
public:
  DelaunayEdge(types::coordinate_t distance);

public:
  types::coordinate_t distance;
};
} // namespace model
} // namespace how
#endif // DELAUNAYEDGE_H
