#include "worldbuilder.h"

#include <iostream>
#include "../../../utils/algo/poissondisksampling.h"

namespace how {
namespace model {

WorldBuilder::WorldBuilder(const types::WorldGenerationConfig& config)
    : min_corner(types::point_t(config.minCornerX, config.minCornerY)),
      max_corner(types::point_t(config.maxCornerX, config.maxCornerY)) {}

WorldData* WorldBuilder::build() const {
  std::cout << "Starting build" << std::endl;
  auto generator = ::how::algo::PoissonDiskSampling<types::point_t>(
      this->min_corner, this->max_corner, 25, 100);
  const auto& points = generator.generateSequence();
  return new WorldData(types::box_t(this->min_corner, this->max_corner),
                       points);
}
}  // namespace model
}  // namespace how
