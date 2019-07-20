#include "modelcontroller.h"

#include "../../model/generation/worldgenerationconfig.h"
#include "../conversion/converter.h"
#include "./savefile.h"

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

void ModelController::saveToFile(QString name) {
  this->modelManager.saveToFile(name.toStdString());
}

void ModelController::loadFromFile(QString name) {
  this->modelManager.loadFromFile(name.toStdString());
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

QList<QObject *> ModelController::getAllSaveFiles() {
  // TODO maybe memory leak
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

} // namespace ui
} // namespace how