#include "graphgenerator.h"

#include <chrono>
#include <iostream>

#include "../utils/easingfunctions.h"
#include "./delaunayextrapolator.h"
#include "./jcv_voronoi_adapter.h"
#include "./poissondisksamplingadapter.h"
#include "./walkingdistancescalculator.h"

namespace how {
namespace model {

void postGenerationOperations(types::graph_t &graph) {
  calculateWalkingDistances(graph);
}

types::graph_t generateGraph(const WorldGenerationConfig &config) {
  const auto &boundingBox = config.boundingBox;
  const auto randomSeed = config.randomSeed;

  std::uint32_t maximumAttempts = 40;
  const auto pdsPoints = generatePoissonDiskSamplingByMinimumDistance(
      config.minimumVoronoiCellDistance, boundingBox, maximumAttempts,
      randomSeed);
  auto tilePtrs = generateVoronoiCells(boundingBox, pdsPoints);
  auto graph = createGraphFromVoronoiCellsAndComputeDelaunayTriangulation(
      tilePtrs, boundingBox);

  postGenerationOperations(graph);

  return graph;
}

types::graph_t generateGraph(const WorldGenerationConfig &config,
                             std::vector<std::shared_ptr<Tile>> tilePtrs) {
  auto graph = createGraphFromVoronoiCellsAndComputeDelaunayTriangulation(
      tilePtrs, config.boundingBox);
  postGenerationOperations(graph);
  return graph;
}

} // namespace model
} // namespace how
