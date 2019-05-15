#include "walkingdistancescalculator.h"

#include <algorithm>
#include <iostream>
namespace how {
namespace model {

void calculateWalkingDistances(types::graph_t &graph) {
  types::graph_edge_iterator_t edgeItBegin;
  types::graph_edge_iterator_t edgeItEnd;
  std::tie(edgeItBegin, edgeItEnd) = ::boost::edges(graph);
  for (auto edgeIt = edgeItBegin; edgeIt != edgeItEnd; edgeIt++) {
    const auto &edgeDesc = *edgeIt;
    const auto &sourceVertexDesc = ::boost::source(edgeDesc, graph);
    const auto &targetVertexDesc = ::boost::target(edgeDesc, graph);
    const auto &sourceVertex = graph[sourceVertexDesc];
    const auto &targetVertex = graph[targetVertexDesc];
    auto &edge = graph[edgeDesc];

    const auto heightDifference =
        targetVertex.getTile().getAltitude() - sourceVertex.getTile().getAltitude();
    const auto walkingDistance =
        edge.getDistanceAsCrowFlies() * (1 + heightDifference);
    edge.setDistanceWalking(std::max(walkingDistance, 0.0F));
  }
}

} // namespace model
} // namespace how
