#include "modelcontroller.h"

#include "../../model/generation/worldgenerationconfig.h"
#include "../conversion/converter.h"

namespace how {
namespace ui {

ModelController::ModelController(QObject *parent)
    : QObject(parent), modelManager(), entitiesController(this->modelManager) {}

void ModelController::newModel(int width, int height,
                               float minimumVoronoiCellDistance,
                               int randomSeed) {
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(config);
  this->newModelGenerated();
}

void ModelController::iterateModel() { this->modelManager.iterateModel(); }


QRect ModelController::getWorldBounds() const {
  return convert(this->modelManager.getDelaunayVoronoiGraphPtr()->getBounds());
}

EntitiesController *ModelController::getEntitiesController() {
  return &this->entitiesController;
}

} // namespace ui
} // namespace how
