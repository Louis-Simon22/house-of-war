#include "graphentitymanager.h"

namespace how {
namespace model {

GraphEntityManager::GraphEntityManager()
    : graphEntityChanges(), graphEntities() {}

void GraphEntityManager::addEntityChange(EntityChange *entityChange) {
  this->graphEntityChanges.push_back(entityChange);
}

void GraphEntityManager::addGraphEntity(GraphEntity *graphEntity) {
  this->graphEntities.push_back(std::unique_ptr<GraphEntity>(graphEntity));
}

const std::vector<std::unique_ptr<GraphEntity>> &
GraphEntityManager::getGraphEntities() const {
  return this->graphEntities;
}

void GraphEntityManager::progressAll(float deltaTime) {
  for (auto it = this->graphEntityChanges.begin();
       it != this->graphEntityChanges.end();) {
    if ((*it)->progress(deltaTime)) {
      it = this->graphEntityChanges.erase(it);
    } else {
      it++;
    }
  }
}

} // namespace model
} // namespace how
