#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include <list>
#include <memory>

#include "../delaunaygraphtypes.h"
#include "entitychange.h"

namespace how {
namespace model {
class EntityChangeManager {
public:
  EntityChangeManager();

  void addMovement(EntityChange* movement);
  void progressAll(float deltaTime);

private:
  std::list<std::unique_ptr<EntityChange>> movements;
};
} // namespace model
} // namespace how

#endif // MOVEMENTMANAGER_H
