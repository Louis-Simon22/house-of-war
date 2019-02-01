#ifndef DELAUNAYEDGE_H
#define DELAUNAYEDGE_H

#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

struct DelaunayEdge {
public:
  DelaunayEdge();
  DelaunayEdge(types::segment_t segment);

public:
  types::segment_t segment;
  types::coordinate_fpt_t distance;
};

} // namespace model
} // namespace how
#endif // DELAUNAYEDGE_H
