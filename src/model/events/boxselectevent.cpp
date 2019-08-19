#include "boxselectevent.h"

#include <boost/geometry/algorithms/convert.hpp>

#include "../operations/collisiondetector.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

BoxSelectEvent::BoxSelectEvent(const types::box_t &box, bool addToSelection)
    : box(box), addToSelection(addToSelection) {}

BoxSelectEvent::~BoxSelectEvent() {}

void BoxSelectEvent::applyEvent(EntitiesManager &entitiesManager,
                                SelectionManager &selectionManager) const {
  if (!this->addToSelection) {
    selectionManager.clearSelection();
  }
  const auto &box = this->box;
  const auto &armyPtrs = entitiesManager.getPlayers()[0].getArmyPtrs();
  auto selectedArmies =
      getCollisions<>(armyPtrs, [&box](const std::shared_ptr<Army> &armyPtr) {
        return armyPtr->getSelectionZone()->isBoxOverlappingZone(box);
      });
  if (!selectedArmies.empty()) {
    selectionManager.addArmySelection(selectedArmies[0].get());
  } else {
    const auto &selectedTilePtrs =
        entitiesManager.getTilesRTree().getValuesByBoxIntersection(box);
    if (!selectedTilePtrs.empty()) {
      selectionManager.addTileSelection(selectedTilePtrs[0].get());
    }
  }
}

} // namespace model
} // namespace how
