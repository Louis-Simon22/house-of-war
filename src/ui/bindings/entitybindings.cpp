#include "entitybindings.h"

namespace how {
namespace ui {

EntityBindings::EntityBindings()
    : QObject(nullptr), interactiveEntity(nullptr), entityChangedConnection() {}

EntityBindings::~EntityBindings() {}

void EntityBindings::bindEntity(model::InteractiveEntity *interactiveEntity) {
  this->interactiveEntity = interactiveEntity;
  entityChangedConnection.disconnect();
  this->entityChangedConnection = interactiveEntity->changedSignal.connect(
      ::boost::bind(&EntityBindings::updateBindings, this));
  this->updateBindings();
}

bool EntityBindings::isVisible() const {
  return this->interactiveEntity && this->interactiveEntity->isSelected();
}

} // namespace ui
} // namespace how
