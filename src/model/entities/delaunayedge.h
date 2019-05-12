#ifndef DELAUNAYEDGE_H
#define DELAUNAYEDGE_H

#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

class DelaunayEdge {
public:
  DelaunayEdge();
  DelaunayEdge(types::segment_t segment);
  ~DelaunayEdge();

public:
  const types::segment_t &getSegment() const;
  const types::coordinate_fpt_t &getDistanceAsCrowFlies() const;
  const types::coordinate_fpt_t &getDistanceWalking() const;
  void setDistanceWalking(types::coordinate_fpt_t distanceWalking);

private:
  types::segment_t segment;
  types::coordinate_fpt_t distanceAsCrowFlies;
  types::coordinate_fpt_t distanceWalking;
};

} // namespace model
} // namespace how
#endif // DELAUNAYEDGE_H
