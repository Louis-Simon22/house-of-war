#include "modelcontroller.h"

#include "../../model/generation/worldgenerationconfig.h"
#include "../conversion/converter.h"

namespace how {
namespace ui {

ModelController::ModelController(QObject *parent)
    : QObject(parent), modelManager(), entitiesController(this->modelManager),
      iterationTimerManager() {
  connect(&this->iterationTimerManager, &IterationTimerManager::iterate, this,
          &ModelController::iterateModel, Qt::QueuedConnection);
}

void ModelController::newModel(int width, int height,
                               float minimumVoronoiCellDistance,
                               int randomSeed) {
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(config);
  this->newModelGenerated();
  this->iterationTimerManager.resumeIterations();
}

void ModelController::iterateModel() { this->modelManager.iterateModel(); }

void ModelController::entitiesMouseEvent(int x, int y, int button) {
  switch (button) {
  case Qt::LeftButton:
    this->modelManager.onSelectionEvent(x, y);
    break;
  case Qt::RightButton:
    this->modelManager.onTargetingEvent(x, y);
    break;
  }
}

QRect ModelController::getWorldBounds() const {
  return convert(this->modelManager.getDelaunayVoronoiGraphPtr()->getBounds());
}

EntitiesController *ModelController::getEntitiesController() {
  return &this->entitiesController;
}

} // namespace ui
} // namespace how
