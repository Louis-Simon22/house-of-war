#include "selectionmanager.h"

#include <algorithm>

namespace how {
namespace model {

SelectionManager::SelectionManager()
    : armySelectedSignal(), tileSelectedSignal(), selections() {}

model::InteractiveEntity *SelectionManager::getSelection() const {
  return this->hasSelection() ? this->selections[0] : nullptr;
}

std::vector<InteractiveEntity *> SelectionManager::getSelections() const {
  return this->selections;
}

bool SelectionManager::hasSelection() const {
  return !this->selections.empty();
}

void SelectionManager::clearSelection() {
  for (auto *selection : this->selections) {
    selection->setSelected(false);
  }
  this->selections.clear();
}

void SelectionManager::addTileSelection(Tile *tileSelection) {
  this->tileSelectedSignal(tileSelection);
  this->addSelection(tileSelection);
}

void SelectionManager::addArmySelection(Army *armySelection) {
  if (this->hasSelection()) {
    this->multiSelectionSignal();
  } else {
    this->armySelectedSignal(armySelection);
  }
  this->addSelection(armySelection);
}

void SelectionManager::removeSelection(InteractiveEntity *selection) {
  selection->setSelected(false);
  this->selections.erase(
      std::remove(this->selections.begin(), this->selections.end(), selection),
      this->selections.end());
}

void SelectionManager::addSelection(InteractiveEntity *selection) {
  selection->setSelected(true);
  this->selections.push_back(selection);
}

} // namespace model
} // namespace how
