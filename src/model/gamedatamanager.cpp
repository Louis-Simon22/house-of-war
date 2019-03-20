#include "gamedatamanager.h"

namespace how {
namespace model {
GameDataManager::GameDataManager()
    : worldDataPtr(std::unique_ptr<WorldData>()),
      characterDataPtr(std::unique_ptr<CharacterData>()) {}

void GameDataManager::newGame(types::WorldGenerationConfig config) {
  this->worldDataPtr.reset(generateWorld(config));
  this->characterDataPtr.reset(generateCharacters());
}

void GameDataManager::loadGame() {
  // TODO
}

WorldData *GameDataManager::getWorldDataPtr() {
  return this->worldDataPtr.get();
}

CharacterData *GameDataManager::getCharacterDataPtr() {
  return this->characterDataPtr.get();
}

} // namespace model
} // namespace how
