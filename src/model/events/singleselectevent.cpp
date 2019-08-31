#include "singleselectevent.h"

#include "../operations/collisiondetector.h"

namespace how {
namespace model {

SingleSelectEvent::SingleSelectEvent(const types::point_t &position, bool add)
    : position(position), addToSelection(add) {}

SingleSelectEvent::~SingleSelectEvent() {}

void SingleSelectEvent::applyEvent(EntitiesManager &entitiesManager,
                                   SelectionManager &selectionManager) const {
  const auto &position = this->position;
  const auto &armyPtrs = entitiesManager.getPlayers()[0].getArmyPtrs();
  auto selectedArmyPtrs = getCollisions<>(
      armyPtrs, [&position](const std::shared_ptr<Army> &armyPtr) {
        return armyPtr->getSelectionZone()->isPointOverlappingZone(position);
      });
  if (!selectedArmyPtrs.empty()) {
    if (!this->addToSelection) {
      selectionManager.clearSelection();
    }
    auto &selectedArmyPtr = selectedArmyPtrs[0];
    if (selectedArmyPtr->isSelected()) {
      selectionManager.removeSelection(selectedArmyPtr.get());
    } else {
      selectionManager.addArmySelection(selectedArmyPtr.get());
    }
  } else {
    const auto &selectedTilePtrs =
        entitiesManager.getTilesRTree().getValuesByPosition(position);
    if (!selectedTilePtrs.empty()) {
      selectionManager.clearSelection();
      selectionManager.addTileSelection(selectedTilePtrs[0].get());
    }
  }
}

} // namespace model
} // namespace how
