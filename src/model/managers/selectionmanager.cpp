#include "selectionmanager.h"

namespace how {
namespace model {

SelectionManager::SelectionManager() : selection(nullptr) {}

void SelectionManager::setSelection(InteractiveEntity *newSelection) {
  if (this->hasSelection()) {
    this->selection->setSelected(false);
  }
  if (newSelection) {
    newSelection->setSelected(true);
  }
  this->selection = newSelection;
}

model::InteractiveEntity *SelectionManager::getSelection() const {
  return this->selection;
}

bool SelectionManager::hasSelection() const { return this->selection; }

void SelectionManager::clearSelection() { this->setSelection(nullptr); }

} // namespace model
} // namespace how
