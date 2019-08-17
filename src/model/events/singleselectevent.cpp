#include "singleselectevent.h"

#include "../operations/collisiondetector.h"

namespace how {
namespace model {

SingleSelectEvent::SingleSelectEvent(const types::point_t &position)
    : SinglePositionEvent(position) {}

SingleSelectEvent::~SingleSelectEvent() {}

void SingleSelectEvent::applyEvent(EntitiesManager &entitiesManager,
                                   SelectionManager &selectionManager) const {
  const auto &position = this->getPosition();
  const auto &armyPtrs = entitiesManager.getPlayers()[0].getArmyPtrs();
  auto selectedArmies = getCollisions<>(
      armyPtrs, [&position](const std::shared_ptr<Army> &armyPtr) {
        return armyPtr->getSelectionZone()->isPointOverlappingZone(position);
      });
  if (!selectedArmies.empty()) {
    selectionManager.addArmySelection(selectedArmies[0].get());
  } else {
    const auto &selectedTilePtrs =
        entitiesManager.getTilesRtree().getValuesByPosition(position);
    if (!selectedTilePtrs.empty()) {
      selectionManager.addTileSelection(selectedTilePtrs[0].get());
    }
  }
}

} // namespace model
} // namespace how
