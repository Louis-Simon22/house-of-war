#include "singleselectevent.h"

#include "../operations/collisiondetector.h"

namespace how {
namespace model {

SingleSelectEvent::SingleSelectEvent(const types::point_t &position, bool add)
    : position(position), addToSelection(add) {}

SingleSelectEvent::~SingleSelectEvent() {}

void SingleSelectEvent::applyEvent(EntitiesManager &entitiesManager,
                                   SelectionManager &selectionManager) const {
  if (!this->addToSelection) {
    selectionManager.clearSelection();
  }
  const auto &position = this->position;
  const auto &armyPtrs = entitiesManager.getPlayers()[0].getArmyPtrs();
  auto selectedArmies = getCollisions<>(
      armyPtrs, [&position](const std::shared_ptr<Army> &armyPtr) {
        return armyPtr->getSelectionZone()->isPointOverlappingZone(position);
      });
  if (!selectedArmies.empty()) {
    selectionManager.addArmySelection(selectedArmies[0].get());
  } else {
    const auto &selectedTilePtrs =
        entitiesManager.getTilesRTree().getValuesByPosition(position);
    if (!selectedTilePtrs.empty()) {
      selectionManager.addTileSelection(selectedTilePtrs[0].get());
    }
  }
}

} // namespace model
} // namespace how
