#include "army.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

Army::Army(types::point_t initialPosition)
    : GraphEntity(Layers::CHARACTERS, initialPosition), selectionZone(1, *this),
      engagementZone(2, *this), foragingZone(3, *this), scoutingZone(4, *this) {
}

Army::~Army() {}

bool Army::isTargetable() const { return false; }

bool Army::isSelectable() const { return true; }

bool Army::isWithinSelectionArea(types::coordinate_t posX,
                                 types::coordinate_t posY) const {
  return this->selectionZone.isPointWithinZone(posX, posY);
}

const CircularInfluenceZone &Army::getSelectionZone() {
  return this->selectionZone;
}

const CircularInfluenceZone &Army::getEngagementZone() {
  return this->engagementZone;
}

const CircularInfluenceZone &Army::getForagingZone() {
  return this->foragingZone;
}

const CircularInfluenceZone &Army::getScoutingZone() {
  return this->scoutingZone;
}

} // namespace model
} // namespace how

// TODO train points as difference from leader
