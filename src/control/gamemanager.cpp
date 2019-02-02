#include "gamemanager.h"
#include <iostream>

namespace how {
namespace control {
GameManager::GameManager() {
  this->worldDataPtr = std::unique_ptr<WorldData>();
}

void GameManager::generateNewWorld(const WorldGenerationConfig &config) {
  auto *worldData = model::buildWorld(config);
  this->worldDataPtr.reset(worldData);
}

const std::vector<model::types::point_t> *
GameManager::getCellCentroids() const {
  return this->worldDataPtr->getCellCentroids();
}

const std::vector<model::types::segment_t> *
GameManager::getUniqueVoronoiSegments() const {
  return this->worldDataPtr->getUniqueVoronoiSegments();
}

const std::vector<model::types::segment_t> *
GameManager::getUniqueDelaunaySegments() const {
  return this->worldDataPtr->getUniqueDelaunaySegments();
}

const ::how::model::types::box_t *GameManager::getWorldBounds() const {
  return this->worldDataPtr->getBounds();
}
} // namespace control
} // namespace how
