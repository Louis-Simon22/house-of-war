#include "worldbuilder.h"

#include <iostream>
#include "../../../utils/algo/poissondisksampling.h"

namespace how {
namespace model {

WorldBuilder::WorldBuilder(types::WorldGenerationConfig config)
    : min_corner(types::point_t(config.minCornerX, config.minCornerY)),
      max_corner(types::point_t(config.maxCornerY, config.maxCornerY)) {}

WorldData* WorldBuilder::build() const {
  //  auto generator =
  //      ::how::algo::PoissonDiskSampling<Point>(min_corner, max_corner, 50,
  //      100, 40);
  //  auto const& points = generator.generateSequence();
  return new WorldData(types::box_t(min_corner, max_corner),
                       std::vector<types::point_t>());
}
}  // namespace model
}  // namespace how
