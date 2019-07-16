#include "worldgenerationconfig.h"

namespace how {
namespace model {

WorldGenerationConfig::WorldGenerationConfig()
    : boundingBox(), minimumVoronoiCellDistance(0), randomSeed(0) {}

WorldGenerationConfig::WorldGenerationConfig(
    types::box_t boundingBox, types::coordinate_t minimumVoronoiCellDistance,
    uint32_t randomSeed)
    : boundingBox(boundingBox),
      minimumVoronoiCellDistance(minimumVoronoiCellDistance),
      randomSeed(randomSeed) {}

WorldGenerationConfig::WorldGenerationConfig(
    types::coordinate_t minCornerX, types::coordinate_t minCornerY,
    types::coordinate_t maxCornerX, types::coordinate_t maxCornerY,
    types::coordinate_t minimumVoronoiCellDistance, uint32_t randomSeed)
    : boundingBox(types::point_t(minCornerX, minCornerY),
                  types::point_t(maxCornerX, maxCornerY)),
      minimumVoronoiCellDistance(minimumVoronoiCellDistance),
      randomSeed(randomSeed) {}

} // namespace model
} // namespace how
