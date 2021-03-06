#ifndef WORLDGENERATIONCONFIG_H
#define WORLDGENERATIONCONFIG_H

#include <string>

#include "../modeltypes.h"

namespace how {
namespace model {
struct WorldGenerationConfig {
public:
  WorldGenerationConfig();
  WorldGenerationConfig(types::box_t boundingBox,
                        types::coordinate_t minimumVoronoiCellDistance,
                        std::uint32_t randomSeed);
  WorldGenerationConfig(types::coordinate_t minCornerX,
                        types::coordinate_t minCornerY,
                        types::coordinate_t maxCornerX,
                        types::coordinate_t maxCornerY,
                        types::coordinate_t minimumVoronoiCellDistance,
                        std::uint32_t randomSeed);

public:
  types::box_t boundingBox;
  types::coordinate_t minimumVoronoiCellDistance;
  std::uint32_t randomSeed;
};
} // namespace model
} // namespace how

#endif // WORLDGENERATIONCONFIG_H
