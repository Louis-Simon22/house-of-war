#include "delaunayedge.h"

#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {

DelaunayEdge::DelaunayEdge(types::segment_t segment)
    : segment(segment),
      distanceAsCrowFlies(static_cast<float>(bg::length(segment))) {}

DelaunayEdge::~DelaunayEdge() {}

const edge_desc_t &DelaunayEdge::getEdgeDesc() const { return this->edgeDesc; }

void DelaunayEdge::setEdgeDesc(const edge_desc_t &edgeDesc) {
  this->edgeDesc = edgeDesc;
}

const types::segment_t &DelaunayEdge::getSegment() const {
  return this->segment;
}

types::coordinate_t DelaunayEdge::getDistanceAsCrowFlies() const {
  return this->distanceAsCrowFlies;
}

types::coordinate_t DelaunayEdge::getWalkingDistance() const {
  return this->walkingDistance;
}

void DelaunayEdge::setWalkingDistance(types::coordinate_t walkingDistance) {
  this->walkingDistance = walkingDistance;
}

} // namespace model
} // namespace how
