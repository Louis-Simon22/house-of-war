#include "worldbuilder.h"

#include <iostream>
#include "../../../utils/algo/poissondisksampling.h"

namespace how {
namespace model {

WorldBuilder::WorldBuilder(const types::WorldGenerationConfig& config)
    : min_corner(types::point_t(config.minCornerX, config.minCornerY)),
      max_corner(types::point_t(config.maxCornerY, config.maxCornerY)) {}

WorldData* WorldBuilder::build() const {
  std::cout << "Starting build" << std::endl;
  auto generator = ::how::algo::PoissonDiskSampling<types::point_t>(
      this->min_corner, this->max_corner, 50, 100, 40);
  const auto& points = generator.generateSequence();
  //  auto point1 = types::point_t(50, 50);
  //  auto points = std::vector<types::point_t>();
  //  points.push_back(point1);
  //  points.push_back(types::point_t(150, 150));
  //  points.push_back(types::point_t(250, 250));
  //  auto count = points.size();
  return new WorldData(types::box_t(this->min_corner, this->max_corner),
                       points);
}
}  // namespace model
}  // namespace how
