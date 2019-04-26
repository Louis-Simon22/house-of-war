#include "modelmanagerqmlwrapper.h"

#include <iostream>

#include "../../model/generation/worldgenerationconfig.h"

namespace how {
namespace ui {
ModelManagerQMLWrapper::ModelManagerQMLWrapper(QObject *parent)
    : QObject(parent), modelManager(model::ModelManager()),
      modelThreadManager(), WorldManagerQMLWrapperPtr(),
      graphEntityManagerQMLWrapper(), charactersControllerPtr() {}
// TODO try to not have all these managers in unique_ptr, maybe default init
// would work?

void ModelManagerQMLWrapper::newGame(int width, int height,
                                     float minimumVoronoiCellDistance,
                                     int randomSeed) {
  this->modelThreadManager.pauseIterations();
  //  std::cout << "New World Generation thread" << this->thread() << std::endl;
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(config);
  this->WorldManagerQMLWrapperPtr.reset(
      new WorldManagerQMLWrapper(this->modelManager.getWorldManagerPtr()));
  this->graphEntityManagerQMLWrapper.reset(new GraphEntityManagerQMLWrapper(
      this->modelManager.getGraphEntityManagerPtr()));
  this->charactersControllerPtr.reset(new CharactersController(
      this->modelManager.getEntityChangeManagerPtr(),
      this->modelManager.getWorldManagerPtr(),
      this->modelManager.getGraphEntityManagerPtr(),
      this->graphEntityManagerQMLWrapper->getCharactersModel()));
  this->modelThreadManager.registerQObjectOnThread(
      this->charactersControllerPtr.get());
  connect(&this->modelThreadManager, &ModelThreadManager::iteration,
          this->charactersControllerPtr.get(),
          &CharactersController::iterateAllChanges);
  this->modelThreadManager.resumeIterations();
  this->newGameGenerated();
}

void ModelManagerQMLWrapper::loadGame() {}

WorldManagerQMLWrapper *
ModelManagerQMLWrapper::getWorldManagerQMLWrapper() const {
  return this->WorldManagerQMLWrapperPtr.get();
}

GraphEntityManagerQMLWrapper *
ModelManagerQMLWrapper::getGraphEntityManagerQMLWrapper() const {
  return this->graphEntityManagerQMLWrapper.get();
}

CharactersController *ModelManagerQMLWrapper::getCharactersController() {
  return this->charactersControllerPtr.get();
}
} // namespace ui
} // namespace how
