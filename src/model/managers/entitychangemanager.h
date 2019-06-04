#ifndef ENTITYCHANGEMANAGER_H
#define ENTITYCHANGEMANAGER_H

#include <list>
#include <memory>

#include "../entities/entitychange.h"
#include "../entities/voronoicell.h"

namespace how {
namespace model {
class EntityChangeManager {
public:
  EntityChangeManager();

public:
  void iterateAllEntityChanges();
  void
  addGraphEntityPositionChange(Entity *source,
                               std::vector<const VoronoiCell *> destinations);

private:
  std::list<std::unique_ptr<EntityChange>> entityChangePtrs;
};
} // namespace model
} // namespace how

#endif // ENTITYCHANGEMANAGER_H
