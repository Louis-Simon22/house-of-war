#include "modelcontroller.h"

#include "../../model/events/editterrainevent.h"
#include "../../model/events/selectevent.h"
#include "../../model/events/targetevent.h"
#include "../../model/generation/worldgenerationconfig.h"
#include "../conversion/converter.h"
#include "./savefile.h"

namespace how {
namespace ui {

ModelController::ModelController(QObject *parent)
    : QObject(parent), modelManager(), entitiesController(this->modelManager),
      iterationTimerManager(), currentControlMode(ControlModeWrapper::EDIT) {
  connect(&this->iterationTimerManager, &IterationTimerManager::iterate, this,
          &ModelController::iterateModel, Qt::QueuedConnection);
}

void ModelController::newModel(QString fileName, int width, int height,
                               float minimumVoronoiCellDistance,
                               int randomSeed) {
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(fileName.toStdString(), config);
  this->newModelGenerated();
}

void ModelController::saveToFile() { this->modelManager.saveToFile(); }

void ModelController::loadFromFile(QString name) {
  this->modelManager.loadFromFile(name.toStdString());
}

void ModelController::iterateModel() { this->modelManager.iterateModel(); }

void ModelController::entitiesMouseEvent(int x, int y, int button) {
  // TODO able to select with a line, circle, square (no need to use zones)
  switch (button) {
  case Qt::LeftButton:
    this->modelManager.onEvent(model::SingleSelectEvent(x, y));
    break;
  case Qt::RightButton:
    switch (this->getControlMode()) {
    case ControlModeWrapper::PLAY:
      this->modelManager.onEvent(model::TargetEvent(x, y));
      break;
    case ControlModeWrapper::EDIT:
      auto terrainType = static_cast<model::TerrainType>(
          this->entitiesController.getTilesController()->getTerrainType());
      this->modelManager.onEvent(model::SingleEditTerrainEvent(x, y, terrainType));
      break;
    }
    break;
  }
}

QList<QObject *> ModelController::getAllSaveFiles() {
  auto saveFiles = QList<QObject *>();
  for (auto &fileName : model::getAllSaveFileNames()) {
    saveFiles.append(new SaveFile(QString::fromStdString(fileName)));
  }
  return saveFiles;
}

QRect ModelController::getWorldBounds() const {
  return convert(this->modelManager.getWorldBounds());
}

EntitiesController *ModelController::getEntitiesController() {
  return &this->entitiesController;
}

IterationTimerManager *ModelController::getIterationTimerManager() {
  return &this->iterationTimerManager;
}

int ModelController::getControlMode() const { return this->currentControlMode; }

void ModelController::setControlMode(int controlMode) {
  this->currentControlMode =
      static_cast<ControlModeWrapper::ControlMode>(controlMode);
  this->controlModeChanged(controlMode);
}

} // namespace ui
} // namespace how
