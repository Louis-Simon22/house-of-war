#include "roadeditevent.h"

namespace how {
namespace model {

RoadEditEvent::RoadEditEvent(const types::segment_t &segment)
    : segment(segment) {}

RoadEditEvent::~RoadEditEvent() {}

void RoadEditEvent::applyEvent(EntitiesManager &entitiesManager,
                               SelectionManager &) const {
  auto &tilesRTree = entitiesManager.getTilesRTree();
  auto tilePtrs = tilesRTree.getValuesBySegmentIntersection(this->segment);
  if (tilePtrs.size() == 2) {
    const auto &tilePtr1 = tilePtrs[0];
    const auto &tilePtr2 = tilePtrs[1];
    tilePtr1->addRoadTo(tilePtr2);
    tilePtr2->addRoadTo(tilePtr1);
  }
}

} // namespace model
} // namespace how
