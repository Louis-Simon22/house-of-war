#ifndef GRAPHENTITYMANAGER_H
#define GRAPHENTITYMANAGER_H

#include <list>
#include <memory>
#include <vector>

#include "../entities/army.h"
#include "../entities/character.h"
#include "../entities/entitychange.h"

namespace how {
namespace model {
class GraphEntityManager {
public:
  GraphEntityManager();

public:
  void addGraphEntity(GraphEntity *graphEntity);
  void addEntityChange(EntityChange *entityChange);
  void progressAll(float deltaTime);

public:
  const std::vector<std::unique_ptr<GraphEntity>> &getGraphEntities() const;

private:
  std::list<EntityChange *> graphEntityChanges;
  std::vector<std::unique_ptr<GraphEntity>> graphEntities;
  // TODO notify when new entity
};
} // namespace model
} // namespace how

#endif // GRAPHENTITYMANAGER_H
