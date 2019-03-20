#include "worldgenerator.h"

#include "../../random/poissondisksampling.h"
#include "delaunayextrapolator.h"

#include <QThread>
#include <chrono>

namespace how {
namespace model {

WorldData *generateWorld(const types::WorldGenerationConfig &config) {
  std::cout << "Starting world generation" << std::endl;
  const auto &start = std::chrono::system_clock::now();
  const auto &minCorner = types::point_t(config.minCornerX, config.minCornerY);
  const auto &maxCorner = types::point_t(config.maxCornerX, config.maxCornerY);
  const auto &boundingBox = types::box_t(minCorner, maxCorner);

  std::cout << "Generating points" << std::endl;
  auto generator =
      PoissonDiskSampling<types::point_t>(minCorner, maxCorner, 30, 40);
  const auto &points = generator.generateSequence();

  std::cout << "Generating voronoi" << std::endl;
  const auto &voronoiPair = buildVoronoi(boundingBox, points);
  const auto &uniqueVoronoiSegments = voronoiPair.first;
  const auto &voronoiCells = voronoiPair.second;

  std::cout << "Generating delaunay" << std::endl;
  const auto &delaunayTuple =
      DelaunayExtrapolator::extrapolateDelaunayTriangulation(voronoiCells);
  const auto &combinedGraph = std::get<0>(delaunayTuple);
  const auto &delaunayEdges = std::get<1>(delaunayTuple);
  const auto &uniqueDelaunaySegments = std::get<2>(delaunayTuple);

  std::cout << "World generated in "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
                   .count()
            << std::endl;
  return new WorldData(boundingBox, points, uniqueVoronoiSegments,
                       uniqueDelaunaySegments, voronoiCells, delaunayEdges,
                       combinedGraph);
}
} // namespace model
} // namespace how
