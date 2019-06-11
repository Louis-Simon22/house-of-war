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

std::shared_ptr<const CircularInfluenceZone> Army::getSelectionZonePtr() const {
  return this->selectionZonePtr;
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
