#include "circularinfluencezone.h"

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

CircularInfluenceZone::CircularInfluenceZone(types::coordinate_t radius,
                                             const Entity *parentEntity)
    : InfluenceZone(parentEntity), radius(radius) {}

CircularInfluenceZone::~CircularInfluenceZone() {}

bool CircularInfluenceZone::isPointWithinZone(
    const types::point_t &position) const {
  auto distance = bg::distance(this->parent->getAbsolutePosition(), position);
  return static_cast<float>(distance) < radius;
}

bool CircularInfluenceZone::isPolygonOverlappingZone(
    const types::polygon_t &polygon) const {
  auto distance = bg::distance(this->parent->getAbsolutePosition(), polygon);
  return static_cast<float>(distance) < radius;
}

bool CircularInfluenceZone::isSegmentOverlappingZone(
    const types::segment_t &segment) const {
  auto distance = bg::distance(this->parent->getAbsolutePosition(), segment);
  return static_cast<float>(distance) < radius;
}

types::box_t CircularInfluenceZone::getEnvelope() const {
  auto posX = this->getAbsolutePosX();
  auto posY = this->getAbsolutePosY();
  return types::box_t(types::point_t(posX - this->radius, posY - this->radius),
                      types::point_t(posX + this->radius, posY + this->radius));
}

types::coordinate_t CircularInfluenceZone::getRadius() const {
  return this->radius;
}

void CircularInfluenceZone::setRadius(types::coordinate_t radius) {
  this->radius = radius;
  this->changeSignal();
}

} // namespace model
} // namespace how
