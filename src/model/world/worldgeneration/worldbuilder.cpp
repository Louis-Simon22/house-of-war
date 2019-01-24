#include "worldbuilder.h"

namespace how {
namespace model {

WorldData* buildWorld(const types::WorldGenerationConfig &config) {
  std::cout << "Starting build" << std::endl;
  const auto &minCorner = types::point_t(config.minCornerX, config.minCornerY);
  const auto &maxCorner = types::point_t(config.maxCornerX, config.maxCornerY);
  const auto &boundingBox = types::box_t(minCorner, maxCorner);
  auto generator = ::how::algo::PoissonDiskSampling<types::point_t>(
      minCorner, maxCorner, 30, 40);
  const auto &points = generator.generateSequence();

  const auto &voronoiPair = buildVoronoi(boundingBox, points);
  const auto &voronoiEdges = voronoiPair.first;
  const auto &voronoiCells = voronoiPair.second;

  return new WorldData(boundingBox, points, voronoiEdges, voronoiCells);
}

} // namespace model
} // namespace how
