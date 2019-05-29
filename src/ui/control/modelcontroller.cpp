#include "modelcontroller.h"

namespace how {
namespace ui {

ModelController::ModelController(QObject *parent)
    : QObject(parent), modelManager() {}

void ModelController::newModel(int width, int height,
                               float minimumVoronoiCellDistance,
                               int randomSeed) {
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(config);
  this->graphEntityControllerPtr.reset(
      new GraphEntityController(this->modelManager.getGraphEntityManagerPtr()));
  this->newModelGenerated();
}

void ModelController::iterateModel() { this->modelManager.iterateModel(); }

GraphEntityController *ModelController::getGraphEntityControllerPtr() {
  return this->graphEntityControllerPtr.get();
}

model::GraphEntityManager *ModelController::getGraphEntityManagerPtr() {
  return this->modelManager.getGraphEntityManagerPtr();
}

} // namespace ui
} // namespace how
