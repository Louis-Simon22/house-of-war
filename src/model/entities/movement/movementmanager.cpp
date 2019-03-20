#include "movementmanager.h"

namespace how {
namespace model {
MovementManager::MovementManager()
    : movements(std::list<std::unique_ptr<EntityMovement>>()) {}

void MovementManager::addMovement(EntityMovement *movement) {
  this->movements.emplace_back(movement);
}

void MovementManager::progressAll(float deltaTime) {
  for (auto it = this->movements.begin(); it != this->movements.end();) {
    if ((*it)->progress(deltaTime)) {
      it = this->movements.erase(it);
    } else {
      it++;
    }
  }
}
} // namespace model
} // namespace how
