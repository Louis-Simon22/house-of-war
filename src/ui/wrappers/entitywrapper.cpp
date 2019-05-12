#include "entitywrapper.h"

namespace how {
namespace ui {

EntityWrapper::EntityWrapper() : QObject(), selected(false) {}

EntityWrapper::~EntityWrapper() {}

bool EntityWrapper::isSelected() const { return this->selected; }

void EntityWrapper::setSelected(bool selected) {
  this->selected = selected;
  this->updateEntityPainter();
}
} // namespace ui
} // namespace how
