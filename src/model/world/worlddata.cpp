#include "worlddata.h"

namespace how {
namespace model {

WorldData::WorldData(types::box_t bounds, std::vector<types::point_t> points, types::vd_t& vd)
    : bounds(bounds), points(points), vd(vd) {}

const std::vector<types::point_t> *WorldData::getPointsList() const {
  return &this->points;
}

const types::box_t &WorldData::getBounds() const { return this->bounds; }

const types::vd_t* WorldData::getVoronoiDiagram() const { return &this->vd; }

} // namespace model
} // namespace how
