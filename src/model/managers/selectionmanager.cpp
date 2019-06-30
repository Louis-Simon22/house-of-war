#include "selectionmanager.h"

#include "../operations/collisiondetector.h"

namespace how {
namespace model {

SelectionManager::SelectionManager(EntitiesManager &entitiesManager)
    : armySelectedSignal(), characterSelectedSignal(), tileSelectedSignal(),
      entitiesManager(entitiesManager), selection(nullptr) {}

void SelectionManager::selectByPosition(const types::point_t &position) {
  const auto &armyPtrs = this->entitiesManager.getPlayers()[0].getArmyPtrs();
  auto selectedArmies = getCollisions<>(
      armyPtrs, [&position](const std::shared_ptr<Army> &armyPtr) {
        return armyPtr->getSelectionZone()->isPointWithinZone(position);
      });
  if (selectedArmies.size() > 0) {
    auto *selectedArmy = selectedArmies[0].get();
    this->setSelection(selectedArmy);
    this->armySelectedSignal(selectedArmy);
  } else {
    const auto &selectedTilePtr =
        this->entitiesManager.getTilesRtree().getValuesByPosition(position);
    if (selectedTilePtr.size() > 0) {
      auto *selectedTile = selectedTilePtr[0].get();
      this->setSelection(selectedTile);
      this->tileSelectedSignal(selectedTile);
    }
  }
}

model::InteractiveEntity *SelectionManager::getSelection() const {
  return this->selection;
}

bool SelectionManager::hasSelection() const { return this->selection; }

void SelectionManager::clearSelection() { this->setSelection(nullptr); }

void SelectionManager::setSelection(InteractiveEntity *newSelection) {
  if (this->hasSelection()) {
    this->selection->setSelected(false);
  }
  if (newSelection) {
    newSelection->setSelected(true);
  }
  this->selection = newSelection;
}

} // namespace model
} // namespace how
