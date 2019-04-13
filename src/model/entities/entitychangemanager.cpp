#include "entitychangemanager.h"

#include <iostream>

namespace how {
namespace model {
EntityChangeManager::EntityChangeManager() : entityChanges() {}

void EntityChangeManager::addEntityChange(EntityChange *entityChange) {
  this->entityChanges.emplace_back(entityChange);
}

void EntityChangeManager::progressAll(float deltaTime) {
  for (auto it = this->entityChanges.begin();
       it != this->entityChanges.end();) {
    if ((*it)->progress(deltaTime)) {
      it = this->entityChanges.erase(it);
    } else {
      it++;
    }
  }
}
} // namespace model
} // namespace how
