#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include <list>
#include <memory>

#include "../../delaunaygraphtypes.h"
#include "entitymovement.h"

namespace how {
namespace model {
class MovementManager {
public:
  MovementManager();

  void addMovement(EntityMovement* movement);
  void progressAll(float deltaTime);

private:
  std::list<std::unique_ptr<EntityMovement>> movements;
};
} // namespace model
} // namespace how

#endif // MOVEMENTMANAGER_H
