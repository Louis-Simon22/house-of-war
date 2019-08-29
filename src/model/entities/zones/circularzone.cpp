#include "circularzone.h"

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

CircularZone::CircularZone(types::coordinate_t radius,
                           const Entity *parentEntity)
    : Zone(parentEntity), radius(radius) {}

CircularZone::~CircularZone() {}

bool CircularZone::isPointOverlappingZone(
    const types::point_t &position) const {
  auto distance = bg::distance(this->parent->getAbsolutePosition(), position);
  return static_cast<float>(distance) < radius;
}

bool CircularZone::isBoxOverlappingZone(const types::box_t &box) const {
  auto distance = bg::distance(this->parent->getAbsolutePosition(), box);
  return static_cast<float>(distance) < radius;
}

bool CircularZone::isSegmentOverlappingZone(
    const types::segment_t &segment) const {
  auto distance = bg::distance(this->parent->getAbsolutePosition(), segment);
  return static_cast<float>(distance) < radius;
}

bool CircularZone::isPolygonOverlappingZone(
    const types::polygon_t &polygon) const {
  auto distance = bg::distance(this->parent->getAbsolutePosition(), polygon);
  return static_cast<float>(distance) < radius;
}

types::box_t CircularZone::getEnvelope() const {
  auto posX = this->getAbsolutePosX();
  auto posY = this->getAbsolutePosY();
  return types::box_t(types::point_t(posX - this->radius, posY - this->radius),
                      types::point_t(posX + this->radius, posY + this->radius));
}

types::coordinate_t CircularZone::getRadius() const { return this->radius; }

void CircularZone::setRadius(types::coordinate_t radius) {
  this->radius = radius;
  this->changeSignal();
}

} // namespace model
} // namespace how
