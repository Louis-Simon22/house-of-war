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

    // TODO distance calculation based on terrain/roads

    edge->setDistanceWalking(edge->getDistanceAsCrowFlies());
  }
}

} // namespace model
} // namespace how
