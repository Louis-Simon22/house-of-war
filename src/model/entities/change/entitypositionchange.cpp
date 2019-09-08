#include "entitypositionchange.h"

#include <boost/geometry/arithmetic/arithmetic.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

EntityPositionChange::EntityPositionChange(
    Entity *entity, std::vector<types::point_t> destinations)
    : entity(entity), destinations(destinations), currentDestinationIndex(0) {}

EntityPositionChange::~EntityPositionChange() {}

std::vector<types::point_t>
EntityPositionChange::getPathAsRelativePoints() const {
  const auto &entityPosition = this->entity->getPosition();
  auto pathPoints = std::vector<types::point_t>({types::point_t(0, 0)});

  for (auto destinationIt = this->destinations.begin() +
                            static_cast<long>(this->currentDestinationIndex);
       destinationIt != this->destinations.end(); destinationIt++) {
    auto pathPoint = *destinationIt;
    bg::subtract_point(pathPoint, entityPosition);
    pathPoints.push_back(pathPoint);
  }

  return pathPoints;
}

bool EntityPositionChange::progress() {
  this->entity->setPosition(this->destinations[this->currentDestinationIndex]);
  this->currentDestinationIndex++;
  return this->isDone();
}

bool EntityPositionChange::isDone() {
  return this->currentDestinationIndex >= this->destinations.size();
}

} // namespace model
} // namespace how
