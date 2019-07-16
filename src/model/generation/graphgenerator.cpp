#include "graphgenerator.h"

#include <chrono>
#include <iostream>

#include "../utils/easingfunctions.h"
#include "./celldatagenerator.h"
#include "./delaunayextrapolator.h"
#include "./jcv_voronoi_adapter.h"
#include "./poissondisksamplingadapter.h"
#include "./walkingdistancescalculator.h"

namespace how {
namespace model {

types::graph_t generateGraph(const WorldGenerationConfig &config) {
  std::cout << "Starting world generation" << std::endl;
  std::cout << "=============================" << std::endl;
  const auto startTime = std::chrono::system_clock::now();
  const auto &boundingBox = config.boundingBox;
  const auto randomSeed = config.randomSeed;

  // PDS points generation
  const std::uint32_t maximumAttempts = 40;
  const auto pdsPoints = generatePoissonDiskSamplingByMinimumDistance(
      config.minimumVoronoiCellDistance, boundingBox, maximumAttempts,
      randomSeed);
  std::cout << "Generated " << pdsPoints.size() << " points "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - startTime)
                   .count()
            << std::endl;
  std::cout << "=============================" << std::endl;

  // Voronoi graph generation
  auto tilePtrs = generateVoronoiCells(boundingBox, pdsPoints);
  std::cout << "Generated voronoi cells "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - startTime)
                   .count()
            << std::endl;
  std::cout << "=============================" << std::endl;

  // Delaunay graph extracion
  auto graph = createGraphFromVoronoiCellsAndComputeDelaunayTriangulation(
      tilePtrs, boundingBox);
  std::cout << "Generated graph "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - startTime)
                   .count()
            << std::endl;
  std::cout << "=============================" << std::endl;

  // Cell data generation
  generateHeightData(boundingBox, randomSeed, graph);
  std::cout << "Generated cell data "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - startTime)
                   .count()
            << std::endl;
  std::cout << "=============================" << std::endl;

  // Walking distance calculation
  calculateWalkingDistances(graph);
  std::cout << "Calculated walking distances "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - startTime)
                   .count()
            << std::endl;
  std::cout << "=============================" << std::endl;

  return graph;
}

types::graph_t generateGraph(const WorldGenerationConfig &config,
                             std::vector<std::shared_ptr<Tile>> tilePtrs) {
    return createGraphFromVoronoiCellsAndComputeDelaunayTriangulation(
                tilePtrs, config.boundingBox);
}

} // namespace model
} // namespace how
