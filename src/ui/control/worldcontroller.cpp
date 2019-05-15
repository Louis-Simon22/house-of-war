#include "worldcontroller.h"

#include "../conversion/converter.h"

namespace how {
namespace ui {

WorldController::WorldController(model::WorldManager *worldManagerPtr)
    : QObject(), worldManagerPtr(worldManagerPtr) {}

const model::WorldManager *WorldController::getWorldManager() const {
  return this->worldManagerPtr;
}

QRect WorldController::getWorldBounds() const {
  return convert(this->worldManagerPtr->getBounds());
}

} // namespace ui
} // namespace how
