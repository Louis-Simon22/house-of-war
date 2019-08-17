#include "army.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

Army::Army(types::point_t initialPosition)
    : InteractiveEntity(Layers::CHARACTERS, initialPosition),
      selectionZone(5, this), engagementZone(5, this), foragingZone(20, this),
      scoutingZone(100, this) {}

Army::~Army() {}

bool Army::isTargetable() const { return false; }

bool Army::isSelectable() const { return true; }

CircularZone *Army::getSelectionZone() { return &this->selectionZone; }

CircularZone *Army::getEngagementZone() {
  return &this->engagementZone;
}

CircularZone *Army::getForagingZone() { return &this->foragingZone; }

CircularZone *Army::getScoutingZone() { return &this->scoutingZone; }

} // namespace model
} // namespace how

// TODO train points as difference from leader
