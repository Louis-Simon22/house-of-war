#include "circularinfluencezone.h"

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

CircularInfluenceZone::CircularInfluenceZone(
    types::coordinate_t radius, const GraphEntity &attachedGraphEntity)
    : InfluenceZone(attachedGraphEntity), radius(radius) {}

CircularInfluenceZone::~CircularInfluenceZone() {}

bool CircularInfluenceZone::isPointWithinZone(types::coordinate_t posX,
                                              types::coordinate_t posY) const {
  auto distance = bg::distance(this->attachedEntity.getPosition(),
                               types::point_t(posX, posY));
  return static_cast<float>(distance) < radius;
}

bool CircularInfluenceZone::isPolygonOverlappingZone(
    types::polygon_t polygon) const {
  auto distance = bg::distance(this->attachedEntity.getPosition(), polygon);
  return static_cast<float>(distance) < radius;
}

types::box_t CircularInfluenceZone::getEnvelope() const {
  auto posX = this->attachedEntity.getPosX();
  auto posY = this->attachedEntity.getPosY();
  return types::box_t(types::point_t(posX - this->radius, posY - this->radius),
                      types::point_t(posX + this->radius, posY + this->radius));
}

types::coordinate_t CircularInfluenceZone::getRadius() const {
  return this->radius;
}

void CircularInfluenceZone::setRadius(types::coordinate_t radius) {
  this->radius = radius;
  this->changedSignal();
}

} // namespace model
} // namespace how
