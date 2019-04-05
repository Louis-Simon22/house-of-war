#include "entitychangemanager.h"

namespace how {
namespace model {
EntityChangeManager::EntityChangeManager()
    : movements(std::list<std::unique_ptr<EntityChange>>()) {}

void EntityChangeManager::addMovement(EntityChange *movement) {
  this->movements.emplace_back(movement);
}

void EntityChangeManager::progressAll(float deltaTime) {
  for (auto it = this->movements.begin(); it != this->movements.end();) {
    const auto &movement = *it;
    if (movement->progress(deltaTime)) {
      it = this->movements.erase(it);
    } else {
      it++;
    }
  }
}
} // namespace model
} // namespace how
