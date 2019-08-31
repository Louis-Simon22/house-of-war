#ifndef DELAUNAYEDGE_H
#define DELAUNAYEDGE_H

#include <memory>

#include <boost/graph/detail/edge.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/graph_traits.hpp>

#include "../modeltypes.h"
#include "./tile.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
using edge_desc_t =
    ::boost::detail::edge_desc_impl<::boost::directed_tag, vertex_desc_t>;
} // namespace

class DelaunayEdge {
public:
  DelaunayEdge(types::segment_t segment);
  ~DelaunayEdge();

public:
  const edge_desc_t &getEdgeDesc() const;
  void setEdgeDesc(const edge_desc_t &edgeDesc);
  const types::segment_t &getSegment() const;
  types::coordinate_t getDistanceAsCrowFlies() const;
  types::coordinate_t getWalkingDistance() const;
  void setWalkingDistance(types::coordinate_t walkingDistance);

private:
  edge_desc_t edgeDesc;
  types::segment_t segment;
  types::coordinate_t distanceAsCrowFlies;
  types::coordinate_t walkingDistance;
};

} // namespace model
} // namespace how
#endif // DELAUNAYEDGE_H
