#include "walkingdistancescalculator.h"

namespace how {
namespace model {

types::coordinate_t getDistanceMultiplier(Tile *tile) {
  switch (tile->getTerrainType()) {
  case FOREST:
    return 2;
  case PLAIN:
    return 1.3f;
  case MOUNTAIN:
    return std::numeric_limits<types::coordinate_t>::infinity();
  }
  return std::numeric_limits<types::coordinate_t>::infinity();
}

void calculateWalkingDistances(types::graph_t &graph) {
  types::graph_edge_iterator_t edgeItBegin;
  types::graph_edge_iterator_t edgeItEnd;
  std::tie(edgeItBegin, edgeItEnd) = ::boost::edges(graph);
  for (auto edgeIt = edgeItBegin; edgeIt != edgeItEnd; edgeIt++) {
    const auto &edgeDesc = *edgeIt;
    auto &edge = graph[edgeDesc];
    const auto &sourceTilePtr = graph[::boost::source(edgeDesc, graph)];
    const auto &targetTilePtr = graph[::boost::target(edgeDesc, graph)];

    auto walkingDistanceMultiplier = types::coordinate_t(1);
    const auto &sourceTileRoads = sourceTilePtr->getRoads();
    if (sourceTileRoads.find(targetTilePtr) == sourceTileRoads.end()) {
      walkingDistanceMultiplier =
          getDistanceMultiplier(sourceTilePtr.get()) * 0.5f +
          getDistanceMultiplier(targetTilePtr.get()) * 0.5f;
    }
    edge->setWalkingDistance(edge->getDistanceAsCrowFlies() *
                             walkingDistanceMultiplier);
  }
}

} // namespace model
} // namespace how
