#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H

#include <memory>

#include "../generation/entitygenerator.h"
#include "../generation/worldgenerationconfig.h"
#include "../generation/worldgenerator.h"
#include "../modeltypes.h"
#include "./entitychangemanager.h"
#include "./graphentitymanager.h"
#include "./worldmanager.h"

namespace how {
namespace model {
class ModelManager {
public:
  ModelManager();

public:
  void newModel(WorldGenerationConfig config);
  WorldManager *getWorldManagerPtr() const;
  GraphEntityManager *getGraphEntityManagerPtr() const;
  EntityChangeManager *getEntityChangeManagerPtr() const;

private:
  // TODO try not having unique_ptr
  std::unique_ptr<WorldManager> worldManagerPtr;
  std::unique_ptr<GraphEntityManager> graphEntityManagerPtr;
  std::unique_ptr<EntityChangeManager> entityChangeManagerPtr;
};
} // namespace model
} // namespace how

#endif // GAMEDATAMANAGER_H
