#include "worldgenerator.h"

#include <chrono>
#include <iostream>

#include "../utils/easingfunctions.h"
#include "./celldatagenerator.h"
#include "./delaunayextrapolator.h"
#include "./poissondisksamplingadapter.h"
#include "./walkingdistancescalculator.h"

namespace how {
namespace model {

WorldManager *generateWorld(const WorldGenerationConfig &config) {
  std::cout << "Starting world generation" << std::endl;
  std::cout << "=============================" << std::endl;
  const auto &startTime = std::chrono::system_clock::now();
  const auto &minCorner = types::point_t(config.minCornerX, config.minCornerY);
  const auto &maxCorner = types::point_t(config.maxCornerX, config.maxCornerY);
  const auto &boundingBox = types::box_t(minCorner, maxCorner);
  const auto &randomSeed = config.randomSeed;

  // Voronoi points generation
  const std::uint32_t maximumAttempts = 40;
  const auto &points = generatePoissonDiskSamplingByMinimumDistance(
      config.minimumVoronoiCellDistance, boundingBox, maximumAttempts,
      randomSeed);
  std::cout << "Generated " << points.size() << " points "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - startTime)
                   .count()
            << std::endl;
  std::cout << "=============================" << std::endl;

  // Voronoi graph generation
  const auto &voronoiPair = generateVoronoi(boundingBox, points);
  const auto &uniqueVoronoiSegments = voronoiPair.first;
  auto voronoiCells = voronoiPair.second;
  std::cout << "Generated voronoi "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - startTime)
                   .count()
            << std::endl;
  std::cout << "=============================" << std::endl;

  // Delaunay graph extracion
  auto delaunayTuple = extractDelaunayTriangulation(voronoiCells);
  auto graph = std::get<0>(delaunayTuple);
  const auto &uniqueDelaunaySegments = std::get<1>(delaunayTuple);
  std::cout << "Generated delaunay "
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

  return new WorldManager(boundingBox, uniqueVoronoiSegments,
                          uniqueDelaunaySegments, graph);
}
} // namespace model
} // namespace how
