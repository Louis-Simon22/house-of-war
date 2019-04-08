#include "gamedatamanager.h"

namespace how {
namespace model {
GameDataManager::GameDataManager()
    : entityChangeManangerPtr(std::make_unique<EntityChangeManager>()),
      worldDataPtr(), characterDataPtr() {}

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

EntityChangeManager *GameDataManager::getEntityChangeManangerPtr() const {
  return this->entityChangeManangerPtr.get();
}

} // namespace model
} // namespace how
