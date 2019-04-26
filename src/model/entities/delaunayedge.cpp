#include "delaunayedge.h"

#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {
DelaunayEdge::DelaunayEdge() : Entity() {}

DelaunayEdge::DelaunayEdge(types::segment_t segment)
    : Entity(), segment(segment),
      distanceAsCrowFlies(static_cast<float>(bg::length(segment))),
      distanceWalking(distanceAsCrowFlies) {}

DelaunayEdge::~DelaunayEdge() {}

const types::segment_t &DelaunayEdge::getSegment() const {
  return this->segment;
}

const types::coordinate_fpt_t &DelaunayEdge::getDistanceAsCrowFlies() const {
  return this->distanceAsCrowFlies;
}

const types::coordinate_fpt_t &DelaunayEdge::getDistanceWalking() const {
  return this->distanceWalking;
}

void DelaunayEdge::setDistanceWalking(types::coordinate_fpt_t distanceWalking) {
  this->distanceWalking = distanceWalking;
}
} // namespace model
} // namespace how
