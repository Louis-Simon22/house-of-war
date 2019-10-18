#include "modelcontroller.h"

#include "../../model/events/boxselectevent.h"
#include "../../model/events/roadeditevent.h"
#include "../../model/events/segmenteditterrainevent.h"
#include "../../model/events/singleeditterrainevent.h"
#include "../../model/events/singleselectevent.h"
#include "../../model/events/targetevent.h"
#include "../../model/generation/worldgenerationconfig.h"
#include "../../model/persistence/savefilesmanager.h"
#include "../conversion/converter.h"
#include "./savefile.h"

#include <iostream>

namespace how {
namespace ui {

ModelController::ModelController(QObject *parent)
    : QObject(parent), modelManager(), entitiesController(this->modelManager),
      iterationTimerManager(),
      currentControlMode(ControlModeWrapper::EDIT_TERRAIN) {
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

void ModelController::entitiesClickEvent(int x, int y, unsigned int button,
                                         unsigned int modifiers) {
  auto position = types::point_t(x, y);
  switch (button) {
  case Qt::LeftButton:
    this->modelManager.onEvent(
        model::SingleSelectEvent(position, modifiers & Qt::ShiftModifier));
    break;
  case Qt::RightButton:
    switch (this->getControlMode()) {
    case ControlModeWrapper::PLAY:
      this->modelManager.onEvent(model::TargetEvent(position));
      break;
    case ControlModeWrapper::EDIT_TERRAIN:
      auto terrainType = static_cast<model::TerrainType>(
          this->entitiesController.getTilesController()->getTerrainType());
      this->modelManager.onEvent(
          model::SingleEditTerrainEvent(position, terrainType));
      break;
    }
    break;
  }
}

void ModelController::entitiesSegmentEvent(int x1, int y1, int x2, int y2,
                                           unsigned int button, unsigned int) {
  auto segment =
      types::segment_t(types::point_t(x1, y1), types::point_t(x2, y2));
  switch (button) {
  case Qt::RightButton:
    switch (this->getControlMode()) {
    case ControlModeWrapper::EDIT_TERRAIN: {
      auto terrainType = static_cast<model::TerrainType>(
          this->entitiesController.getTilesController()->getTerrainType());
      this->modelManager.onEvent(
          model::SegmentEditTerrainEvent(segment, terrainType));
      break;
    }
    case ControlModeWrapper::EDIT_ROADS: {
      // TODO check why this doesnt show
      this->modelManager.onEvent(model::RoadEditEvent(segment));
      break;
    }
    }
    break;
  }
}

void ModelController::entitiesBoxEvent(int x1, int y1, int x2, int y2,
                                       unsigned int, unsigned int modifiers) {
  auto box = types::box_t(types::point_t(x1, y1), types::point_t(x2, y2));
  this->modelManager.onEvent(
      model::BoxSelectEvent(box, modifiers & Qt::ShiftModifier));
}

QList<QObject *> ModelController::getAllSaveFiles() {
  auto saveFiles = QList<QObject *>();
  for (auto &fileName : model::getAllSaveFileNames()) {
    saveFiles.append(new SaveFile(QString::fromStdString(fileName)));
  }
  return saveFiles;
}

void ModelController::iterateModel() { this->modelManager.iterateModel(); }

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

int ModelController::getUiLayer() const { return Layers::UI; }

} // namespace ui
} // namespace how
