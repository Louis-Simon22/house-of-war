#include "worldmanagerwrapper.h"

#include "../conversion/converter.h"

namespace how {
namespace ui {

WorldManagerWrapper::WorldManagerWrapper(model::WorldManager *worldManagerPtr)
    : QObject(), worldManagerPtr(worldManagerPtr) {}

const model::WorldManager *WorldManagerWrapper::getWorldManager() const {
  return this->worldManagerPtr;
}

QRect WorldManagerWrapper::getWorldBounds() const {
  return convert(this->worldManagerPtr->getBounds());
}

} // namespace ui
} // namespace how
