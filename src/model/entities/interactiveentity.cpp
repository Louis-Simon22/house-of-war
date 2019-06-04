#include "interactiveentity.h"

namespace how {
namespace model {

InteractiveEntity::InteractiveEntity(types::layer_t layer,
                                     types::point_t position)
    : Entity(layer, position), selected(false) {}

InteractiveEntity::~InteractiveEntity() {}

bool InteractiveEntity::isSelected() const { return this->selected; }

void InteractiveEntity::setSelected(bool selected) {
  this->selected = selected;
  this->changedSignal();
}

} // namespace model
} // namespace how
