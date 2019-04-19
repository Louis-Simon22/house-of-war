#include "gamedatamanagerqmlwrapper.h"

#include <iostream>

namespace how {
namespace ui {
GameDataManagerQMLWrapper::GameDataManagerQMLWrapper(QObject *parent)
    : QObject(parent), gameDataManager(model::GameDataManager()),
      modelThreadManager(), worldDataQMLWrapperPtr(),
      characterDataQMLWrapperPtr(), charactersControllerPtr() {}

void GameDataManagerQMLWrapper::newGame(int width, int height,
                                        float minimumVoronoiCellDistance,
                                        int randomSeed) {
  this->modelThreadManager.pauseIterations();
  std::cout << "New World Generation thread" << this->thread() << std::endl;
  auto config = types::WorldGenerationConfig();
  config.minCornerX = 0;
  config.minCornerY = 0;
  config.maxCornerX = width;
  config.maxCornerY = height;
  config.minimumVoronoiCellDistance = minimumVoronoiCellDistance;
  config.randomSeed = static_cast<std::uint32_t>(randomSeed);
  this->gameDataManager.newGame(config);
  this->worldDataQMLWrapperPtr.reset(
      new WorldDataQMLWrapper(this->gameDataManager.getWorldDataPtr()));
  this->characterDataQMLWrapperPtr.reset(
      new CharacterDataQMLWrapper(this->gameDataManager.getCharacterDataPtr()));
  this->charactersControllerPtr.reset(new CharactersController(
      this->gameDataManager.getEntityChangeManangerPtr(),
      this->gameDataManager.getWorldDataPtr(),
      this->gameDataManager.getCharacterDataPtr(),
      this->characterDataQMLWrapperPtr->getCharactersModel()));
  this->modelThreadManager.registerQObjectOnThread(
      this->charactersControllerPtr.get());
  connect(&this->modelThreadManager, &ModelThreadManager::iteration,
          this->charactersControllerPtr.get(),
          &CharactersController::iterateAllChanges);
  this->modelThreadManager.resumeIterations();
  this->newGameGenerated();
}

void GameDataManagerQMLWrapper::loadGame() {}

WorldDataQMLWrapper *GameDataManagerQMLWrapper::getWorldDataQMLWrapper() const {
  return this->worldDataQMLWrapperPtr.get();
}

CharacterDataQMLWrapper *
GameDataManagerQMLWrapper::getCharacterDataQMLWrapper() const {
  return this->characterDataQMLWrapperPtr.get();
}

CharactersController *GameDataManagerQMLWrapper::getCharactersController() {
  return this->charactersControllerPtr.get();
}
} // namespace ui
} // namespace how
