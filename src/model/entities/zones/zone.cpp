#include "zone.h"

#include <boost/geometry/algorithms/convert.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

Zone::Zone(const Entity *parentEntity) : Entity(parentEntity) {}

Zone::~Zone() {}

bool Zone::isBoxOverlappingZone(const types::box_t &box) const {
  auto polygon = types::polygon_t();
  bg::convert(box, polygon);
  return this->isPolygonOverlappingZone(polygon);
}

} // namespace model
} // namespace how
