#include "worlddata.h"

namespace how {
namespace model {
WorldData::WorldData(types::box_t bounds, std::vector<types::point_t> points)
    : bounds(bounds), points(points) {}

const std::vector<types::point_t>& WorldData::getPointsList() const {
  return this->points;
}

const types::box_t& WorldData::getBounds() const { return this->bounds; }
}  // namespace model
}  // namespace how
