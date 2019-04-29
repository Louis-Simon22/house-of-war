#include "modelmanager.h"

namespace how {
namespace model {
ModelManager::ModelManager()
    : worldManagerPtr(), graphEntityManagerPtr(),
      entityChangeManagerPtr(std::make_unique<EntityChangeManager>()) {}

void ModelManager::newModel(WorldGenerationConfig config) {
  this->worldManagerPtr.reset(generateWorld(config));
  this->graphEntityManagerPtr = std::make_unique<GraphEntityManager>(
      generateCharacters(this->worldManagerPtr->getGraph()),
      std::vector<Army>());
  // todo generate armies}

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
