#include "gamemanager.h"
#include <iostream>

namespace how {
namespace control {
GameManager::GameManager() {
  this->modelFacadePtr = std::make_unique<ModelFacade>();
}

void GameManager::generateNewWorld(const WorldGenerationConfig& config) {
  this->modelFacadePtr->generateNewWorld(config);
}

const std::vector<model::types::point_t>* GameManager::getPointsList() const {
  return this->modelFacadePtr->getPointsList();
}

const ::how::model::types::box_t GameManager::getWorldBounds() const {
  return this->modelFacadePtr->getWorldBounds();
}
}  // namespace control
}  // namespace how
