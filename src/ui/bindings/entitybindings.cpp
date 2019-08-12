#include "entitybindings.h"

namespace how {
namespace ui {

EntityBindings::EntityBindings()
    : QObject(nullptr), interactiveEntity(nullptr), entityChangeConnection() {}

EntityBindings::~EntityBindings() {}

void EntityBindings::bindEntity(model::InteractiveEntity *interactiveEntity) {
  this->interactiveEntity = interactiveEntity;
  this->entityChangeConnection.disconnect();
  this->entityChangeConnection = interactiveEntity->changeSignal.connect(
      std::bind(&EntityBindings::updateBindings, this));
  this->updateBindings();
}

bool EntityBindings::isVisible() const {
  return this->interactiveEntity && this->interactiveEntity->isSelected();
}

} // namespace ui
} // namespace how
