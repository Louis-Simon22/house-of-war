#include "gamedatamanagerqmlwrapper.h"

#include <iostream>

namespace how {
namespace ui {
GameDataManagerQMLWrapper::GameDataManagerQMLWrapper(QObject *parent)
    : QObject(parent),
      gameDataManagerPtr(std::make_unique<model::GameDataManager>()) {}

void GameDataManagerQMLWrapper::newGame(int width, int height) {
  std::cout << "New World Generation thread" << this->thread() << std::endl;
  auto config = model::types::WorldGenerationConfig();
  config.minCornerX = 0;
  config.minCornerY = 0;
  config.maxCornerX = width;
  config.maxCornerY = height;
  this->gameDataManagerPtr->newGame(config);
  this->newGameGenerated();
}

void GameDataManagerQMLWrapper::loadGame() {}

WorldDataQMLWrapper *GameDataManagerQMLWrapper::getWorldDataQMLWrapper() const {
  return new WorldDataQMLWrapper(this->gameDataManagerPtr->getWorldDataPtr());
}

CharacterDataQMLWrapper *GameDataManagerQMLWrapper::getCharacterDataQMLWrapper() const {
  return new CharacterDataQMLWrapper(
      this->gameDataManagerPtr->getCharacterDataPtr());
}
} // namespace ui
} // namespace how
