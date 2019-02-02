#include "worldbuilder.h"
#include "delaunayextrapolator.h"

namespace how {
namespace model {

WorldData *buildWorld(const types::WorldGenerationConfig &config) {
  std::cout << "Starting build" << std::endl;
  const auto &minCorner = types::point_t(config.minCornerX, config.minCornerY);
  const auto &maxCorner = types::point_t(config.maxCornerX, config.maxCornerY);
  const auto &boundingBox = types::box_t(minCorner, maxCorner);
  auto generator = ::how::algo::PoissonDiskSampling<types::point_t>(
      minCorner, maxCorner, 30, 40);
  const auto &points = generator.generateSequence();

  const auto &voronoiPair = buildVoronoi(boundingBox, points);
  const auto &uniqueVoronoiSegments = voronoiPair.first;
  const auto &voronoiCells = voronoiPair.second;

  const auto &delaunayTuple =
      DelaunayExtrapolator::extrapolateDelaunayTriangulation(voronoiCells);
  const auto &combinedGraph = std::get<0>(delaunayTuple);
  const auto &delaunayEdges = std::get<1>(delaunayTuple);
  const auto &uniqueDelaunaySegments = std::get<2>(delaunayTuple);

  return new WorldData(boundingBox, points, uniqueVoronoiSegments,
                       uniqueDelaunaySegments, voronoiCells, delaunayEdges,
                       combinedGraph);
}

} // namespace model
} // namespace how
