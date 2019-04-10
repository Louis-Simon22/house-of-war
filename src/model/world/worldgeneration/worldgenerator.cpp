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

  const auto &points =
      PoissonDiskSampling<types::point_t>(minCorner, maxCorner, 30, 40)
          .generateSequence();
  std::cout << "Generated points "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
                   .count()
            << std::endl;

  const auto &voronoiPair = buildVoronoi(boundingBox, points);
  const auto &uniqueVoronoiSegments = voronoiPair.first;
  const auto &voronoiCells = voronoiPair.second;
  std::cout << "Generated voronoi "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
                   .count()
            << std::endl;

  const auto &delaunayTuple = extrapolateDelaunayTriangulation(voronoiCells);
  const auto &delaunayGraph = std::get<0>(delaunayTuple);
  const auto &delaunayEdges = std::get<1>(delaunayTuple);
  const auto &uniqueDelaunaySegments = std::get<2>(delaunayTuple);
  std::cout << "Generated delaunay "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
                   .count()
            << std::endl;

  auto generator = ::boost::random::mt19937();
  for (auto voronoiCell : voronoiCells) {
    voronoiCell.cellData.elevation =
        floating01<::boost::random::mt19937, float>(generator);
  }
  std::cout << "Generated cell data "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
                   .count()
            << std::endl;

  return new WorldData(boundingBox, points, uniqueVoronoiSegments,
                       uniqueDelaunaySegments, voronoiCells, delaunayEdges,
                       delaunayGraph);
}
} // namespace model
} // namespace how
