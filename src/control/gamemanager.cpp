#include "gamemanager.h"
#include <iostream>

namespace how {
namespace control {
GameManager::GameManager() {
  this->worldDataPtr = std::make_unique<WorldData>();
}

void GameManager::generateNewWorld(const WorldGenerationConfig &config) {
  auto *worldData = model::buildWorld(config);
  this->worldDataPtr.reset(worldData);
}

const std::vector<model::types::point_t> *GameManager::getPointsList() const {
  return this->worldDataPtr->getPointsList();
}

const std::vector<model::types::segment_t> *
GameManager::getOutlineSegments() const {
  return this->worldDataPtr->getOutlineSegments();
}

const ::how::model::types::box_t GameManager::getWorldBounds() const {
  return this->worldDataPtr->getBounds();
}
} // namespace control
} // namespace how
