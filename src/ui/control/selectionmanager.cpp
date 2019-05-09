#include "selectionmanager.h"

namespace how {
namespace ui {
SelectionManager::SelectionManager() : QObject(), selection(nullptr) {}

bool SelectionManager::hasSelection() const { return this->selection; }

void SelectionManager::clearSelection() { this->selection = nullptr; }

void SelectionManager::selectEntity(SelectableEntityWrapper *newSelection) {
  if (this->selection) {
    this->selection->setSelected(false);
  }
  newSelection->setSelected(true);
  this->selection = newSelection;
}
} // namespace ui
} // namespace how
