#include "delaunayedge.h"

#include <boost/geometry/strategies/strategies.hpp>
#include <boost/geometry/algorithms/length.hpp>

namespace how {
namespace model {
DelaunayEdge::DelaunayEdge() {}

DelaunayEdge::DelaunayEdge(types::segment_t segment)
    : segment(segment), distance(static_cast<float>(bg::length(segment))) {}
} // namespace model
} // namespace how
