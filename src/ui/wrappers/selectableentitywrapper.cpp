#include "selectableentitywrapper.h"

namespace how {
namespace ui {
SelectableEntityWrapper::SelectableEntityWrapper()
    : EntityWrapper(), selected(false) {}

SelectableEntityWrapper::~SelectableEntityWrapper() {}

bool SelectableEntityWrapper::isSelectable() const { return true; }

void SelectableEntityWrapper::setSelected(bool selected) {
  this->selected = selected;
  this->updateEntityPainter();
}
} // namespace ui
} // namespace how
