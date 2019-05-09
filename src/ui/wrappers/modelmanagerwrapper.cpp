#include "modelmanagerwrapper.h"

#include <memory>

#include <QQmlEngine>

#include "../../model/generation/worldgenerationconfig.h"
#include "../conversion/converter.h"
#include "./armywrapper.h"
#include "./characterwrapper.h"
#include "./entitywrapper.h"
#include "./voronoicellwrapper.h"

#include <iostream>

namespace how {
namespace ui {

ModelManagerWrapper::ModelManagerWrapper(model::ModelManager *modelManagerPtr)
    : QObject(), modelManagerPtr(modelManagerPtr) {}

void ModelManagerWrapper::newModel(int width, int height,
                                   float minimumVoronoiCellDistance,
                                   int randomSeed) {
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManagerPtr->newModel(config);
  this->instantiateEntityWrappers();
  this->newModelGenerated();
}

QRect ModelManagerWrapper::getWorldBounds() const {
  return convert(this->modelManagerPtr->getWorldManagerPtr()->getBounds());
}

} // namespace ui
} // namespace how
