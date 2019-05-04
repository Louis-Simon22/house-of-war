#include "modelmanager.h"

#include "../generation/entitygenerator.h"

namespace how {
namespace model {
ModelManager::ModelManager()
    : worldManagerPtr(), graphEntityManagerPtr(),
      entityChangeManagerPtr(std::make_unique<EntityChangeManager>()) {}

void ModelManager::newModel(WorldGenerationConfig config) {
  this->worldManagerPtr.reset(generateWorld(config));
  const auto &characters =
      generateCharacters(this->worldManagerPtr->getGraph());
  const auto &armies = generateArmies(this->worldManagerPtr->getGraph());
  this->graphEntityManagerPtr =
      std::make_unique<GraphEntityManager>(characters, armies);
}

WorldManager *ModelManager::getWorldManagerPtr() const {
  return this->worldManagerPtr.get();
}

GraphEntityManager *ModelManager::getGraphEntityManagerPtr() const {
  return this->graphEntityManagerPtr.get();
}

EntityChangeManager *ModelManager::getEntityChangeManagerPtr() const {
  return this->entityChangeManagerPtr.get();
}

} // namespace model
} // namespace how
