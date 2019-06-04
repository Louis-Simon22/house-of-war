#include "entitychangemanager.h"

#include "../entities/entitypositionchange.h"

namespace how {
namespace model {

EntityChangeManager::EntityChangeManager() : entityChangePtrs() {}

void EntityChangeManager::addGraphEntityPositionChange(
    Entity *source, std::vector<const VoronoiCell *> destinations) {
  this->entityChangePtrs.push_back(
      std::make_unique<EntityPositionChange>(source, destinations));
}

void EntityChangeManager::iterateAllEntityChanges() {
  for (auto it = this->entityChangePtrs.begin();
       it != this->entityChangePtrs.end();) {
    if ((*it)->progress()) {
      it = this->entityChangePtrs.erase(it);
    } else {
      it++;
    }
  }
}

} // namespace model
} // namespace how
