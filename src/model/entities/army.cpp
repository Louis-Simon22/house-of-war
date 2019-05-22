#include "army.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

Army::Army(types::point_t initialPosition)
    : GraphEntity(Layers::CHARACTERS, initialPosition) {}

Army::~Army() {}

bool Army::isTargetable() const { return false; }

bool Army::isSelectable() const { return true; }

bool Army::isWithinSelectionArea(types::coordinate_t posX,
                                 types::coordinate_t posY) const {
  return true;
}

types::coordinate_t Army::getDetectionRadius() const { return 6; }

void Army::onIteration(float deltaTime) {
  auto minPoint = this->getPosition();
  auto maxPoint = this->getPosition();
  bg::subtract_value(minPoint, this->influenceAreaWidth / 2);
  bg::add_value(maxPoint, this->influenceAreaWidth / 2);
  const auto area = types::box_t(minPoint, maxPoint);
  // TODO influence neighboring tiles
}

} // namespace model
} // namespace how
