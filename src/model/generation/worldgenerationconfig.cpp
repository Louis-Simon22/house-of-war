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

} // namespace model
} // namespace how
