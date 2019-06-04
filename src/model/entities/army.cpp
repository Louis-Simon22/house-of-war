#include "army.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

Army::Army(types::point_t initialPosition)
    : InteractiveEntity(Layers::CHARACTERS, initialPosition),
      selectionZonePtr(std::make_shared<CircularInfluenceZone>(5, this)),
      engagementZonePtr(std::make_shared<CircularInfluenceZone>(5, this)),
      foragingZonePtr(std::make_shared<CircularInfluenceZone>(20, this)),
      scoutingZonePtr(std::make_shared<CircularInfluenceZone>(100, this)) {}

Army::~Army() {}

bool Army::isTargetable() const { return false; }

bool Army::isSelectable() const { return true; }

bool Army::isWithinSelectionArea(types::coordinate_t posX,
                                 types::coordinate_t posY) const {
  return this->selectionZonePtr->isPointWithinZone(posX, posY);
}

std::shared_ptr<CircularInfluenceZone> Army::getEngagementZonePtr() const {
  return this->engagementZonePtr;
}

std::shared_ptr<CircularInfluenceZone> Army::getForagingZonePtr() const {
  return this->foragingZonePtr;
}

std::shared_ptr<CircularInfluenceZone> Army::getScoutingZonePtr() const {
  return this->scoutingZonePtr;
}

} // namespace model
} // namespace how

// TODO train points as difference from leader
