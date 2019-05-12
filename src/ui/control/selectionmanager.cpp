#include "selectionmanager.h"

namespace how {
namespace ui {

SelectionManager::SelectionManager() : QObject(), selection(nullptr) {}

void SelectionManager::selectEntity(EntityWrapper *newSelection) {
  if (this->hasSelection()) {
    this->selection->setSelected(false);
  }
  newSelection->setSelected(true);
  this->selection = newSelection;
}

EntityWrapper *SelectionManager::getSelection() const {
  return this->selection;
}

bool SelectionManager::hasSelection() const { return this->selection; }

void SelectionManager::clearSelection() { this->selection = nullptr; }

} // namespace ui
} // namespace how
