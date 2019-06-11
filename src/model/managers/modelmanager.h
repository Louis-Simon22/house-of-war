#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H

#include <memory>

#include "../generation/worldgenerationconfig.h"
#include "./delaunayvoronoigraph.h"
#include "./entitiesmanager.h"
#include "./entitychangemanager.h"
#include "./selectionmanager.h"

namespace how {
namespace model {
class ModelManager {
public:
  ModelManager();

public:
  void newModel(const WorldGenerationConfig &config);
  void iterateModel();
  void addGraphEntityPositionChange(Entity *source, const Entity *destination);

public:
  EntityChangeManager *getEntityChangeManager();
  EntitiesManager *getEntitiesManager();
  const GraphManager *getDelaunayVoronoiGraphPtr() const;

private:
  EntityChangeManager entityChangeManager;
  EntitiesManager entitiesManager;
  SelectionManager selectionManager;
  std::unique_ptr<GraphManager> delaunayVoronoiGraphPtr;
};
} // namespace model
} // namespace how

#endif // GAMEDATAMANAGER_H
