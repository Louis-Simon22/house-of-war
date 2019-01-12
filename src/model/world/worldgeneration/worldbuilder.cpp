#include "worldbuilder.h"

#include "../../../utils/algo/poissondisksampling.h"
#include <iostream>

namespace how {
namespace model {

WorldBuilder::WorldBuilder(const types::WorldGenerationConfig &config)
    : min_corner(types::point_t(config.minCornerX, config.minCornerY)),
      max_corner(types::point_t(config.maxCornerX, config.maxCornerY)) {}

WorldData *WorldBuilder::build() const {
  std::cout << "Starting build" << std::endl;
  auto generator = ::how::algo::PoissonDiskSampling<types::point_t>(
      this->min_corner, this->max_corner, 30, 40);
  const auto &points = generator.generateSequence();
  auto segments = std::vector<types::segment_t>();
  segments.push_back(types::segment_t(
      this->min_corner, types::point_t(bg::get<0>(this->min_corner),
                                       bg::get<1>(this->max_corner))));
  segments.push_back(types::segment_t(
      this->min_corner, types::point_t(bg::get<0>(this->max_corner),
                                       bg::get<1>(this->min_corner))));
  segments.push_back(
      types::segment_t(types::point_t(bg::get<0>(this->max_corner),
                                      bg::get<1>(this->min_corner)),
                       this->max_corner));
  segments.push_back(
      types::segment_t(types::point_t(bg::get<0>(this->min_corner),
                                      bg::get<1>(this->max_corner)),
                       this->max_corner));
  types::vd_t vd;
  ::boost::polygon::construct_voronoi(points.begin(), points.end(), &vd);
  return new WorldData(types::box_t(this->min_corner, this->max_corner), points,
                       vd);
}
} // namespace model
} // namespace how
