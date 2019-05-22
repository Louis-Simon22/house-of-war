#include "worldgenerationconfig.h"

namespace how {
namespace model {

WorldGenerationConfig::WorldGenerationConfig(
    types::coordinate_t minCornerX, types::coordinate_t minCornerY,
    types::coordinate_t maxCornerX, types::coordinate_t maxCornerY,
    types::coordinate_t minimumVoronoiCellDistance, uint32_t randomSeed)
    : minCornerX(minCornerX), minCornerY(minCornerY), maxCornerX(maxCornerX),
      maxCornerY(maxCornerY),
      minimumVoronoiCellDistance(minimumVoronoiCellDistance),
      randomSeed(randomSeed) {}

types::box_t WorldGenerationConfig::getBoundingBox() const {
  const auto &minCorner = types::point_t(this->minCornerX, this->minCornerY);
  const auto &maxCorner = types::point_t(this->maxCornerX, this->maxCornerY);
  return types::box_t(minCorner, maxCorner);
}

} // namespace model
} // namespace how
