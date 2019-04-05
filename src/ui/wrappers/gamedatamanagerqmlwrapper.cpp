#include "gamedatamanagerqmlwrapper.h"

#include <iostream>

namespace how {
namespace ui {
GameDataManagerQMLWrapper::GameDataManagerQMLWrapper(QObject *parent)
    : QObject(parent), gameDataManager(model::GameDataManager()) {}

void GameDataManagerQMLWrapper::newGame(int width, int height) {
  this->modelThreadManager.pauseIterations();
  std::cout << "New World Generation thread" << this->thread() << std::endl;
  auto config = model::types::WorldGenerationConfig();
  config.minCornerX = 0;
  config.minCornerY = 0;
  config.maxCornerX = width;
  config.maxCornerY = height;
  this->gameDataManager.newGame(config);
  this->newGameGenerated();
}

void GameDataManagerQMLWrapper::loadGame() {}

WorldDataQMLWrapper *GameDataManagerQMLWrapper::getWorldDataQMLWrapper() const {
  return new WorldDataQMLWrapper(this->gameDataManager.getWorldDataPtr());
}

CharacterDataQMLWrapper *
GameDataManagerQMLWrapper::getCharacterDataQMLWrapper() const {
  return new CharacterDataQMLWrapper(
      this->gameDataManager.getCharacterDataPtr());
}

CharactersController *GameDataManagerQMLWrapper::getCharactersController() {
  auto *charactersController =
      new CharactersController(this->gameDataManager.getMovementManagerPtr(),
                               this->gameDataManager.getWorldDataPtr(),
                               this->gameDataManager.getCharacterDataPtr());
  this->modelThreadManager.registerQObjectOnThread(charactersController);
  connect(&this->modelThreadManager, &ModelThreadManager::workerThreadIteration,
          charactersController, &CharactersController::movementIteration);
  this->modelThreadManager.resumeIterations();
  return charactersController;
}
} // namespace ui
} // namespace how
