#include "selectionmanager.h"

namespace how {
namespace ui {

SelectionManager::SelectionManager() : QObject(), selection(nullptr) {}

void SelectionManager::setSelection(model::GraphEntity *newSelection) {
  if (this->hasSelection()) {
    this->selection->setSelected(false);
  }
  newSelection->setSelected(true);
  this->selection = newSelection;
}

model::GraphEntity *SelectionManager::getSelection() const {
  return this->selection;
}

bool SelectionManager::hasSelection() const { return this->selection; }

void SelectionManager::clearSelection() { this->selection = nullptr; }

} // namespace ui
} // namespace how
