#include "gamedatamanager.h"

namespace how {
namespace model {
GameDataManager::GameDataManager()
    : movementManagerPtr(std::make_unique<MovementManager>()),
      worldDataPtr(std::unique_ptr<WorldData>()),
      characterDataPtr(std::unique_ptr<CharacterData>()) {}

void GameDataManager::newGame(types::WorldGenerationConfig config) {
  this->worldDataPtr.reset(generateWorld(config));
  this->characterDataPtr.reset(
      generateCharacters(this->worldDataPtr->getGraph()));
}

WorldData *GameDataManager::getWorldDataPtr() const {
  return this->worldDataPtr.get();
}

CharacterData *GameDataManager::getCharacterDataPtr() const {
  return this->characterDataPtr.get();
}

MovementManager *GameDataManager::getMovementManagerPtr() const {
  return this->movementManagerPtr.get();
}

} // namespace model
} // namespace how
