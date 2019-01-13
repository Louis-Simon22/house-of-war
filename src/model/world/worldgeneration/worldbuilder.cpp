#include "worldbuilder.h"

#include "../../../utils/algo/poissondisksampling.h"
#include "boost/polygon/point_data.hpp"
#include "boost/polygon/segment_data.hpp"
#include "voronoi_util.h"

namespace how {
namespace model {
using polygon_point_t = ::boost::polygon::point_data<types::coordinate_fpt_t>;
using voronoi_utils_t = ::boost::polygon::voronoi_utils<types::coordinate_fpt_t>;

WorldBuilder::WorldBuilder(const types::WorldGenerationConfig &config)
    : min_corner(types::point_t(config.minCornerX, config.minCornerY)),
      max_corner(types::point_t(config.maxCornerX, config.maxCornerY)) {}

WorldData *WorldBuilder::build() const {
  std::cout << "Starting build" << std::endl;
  auto generator = ::how::algo::PoissonDiskSampling<types::point_t>(
      this->min_corner, this->max_corner, 30, 40);
  const auto &points = generator.generateSequence();
  auto polygonPoints = std::vector<polygon_point_t>();
  for (auto &point : points) {
    polygonPoints.push_back(
        polygon_point_t(static_cast<types::coordinate_fpt_t>(bg::get<0>(point)), static_cast<types::coordinate_fpt_t>(bg::get<1>(point))));
  }
  types::vd_t vd;
  ::boost::polygon::construct_voronoi(polygonPoints.begin(), polygonPoints.end(), &vd);
  auto discretizedPoints = voronoi_utils_t::point_set_type();
  for (types::vd_t::const_edge_iterator it = vd.edges().begin();
       it != vd.edges().end(); ++it) {
    voronoi_utils_t::discretize(it->cell(), static_cast<types::coordinate_fpt_t>(50), discretizedPoints);
  }
  return new WorldData(types::box_t(this->min_corner, this->max_corner), points,
                       vd);
}
} // namespace model
} // namespace how
