#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H

#include <memory>

#include "../generation/worldgenerationconfig.h"
#include "./delaunayvoronoigraph.h"
#include "./entitiesmanager.h"
#include "./entitychangemanager.h"

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
  const DelaunayVoronoiGraph *getDelaunayVoronoiGraphPtr() const;

private:
  EntityChangeManager entityChangeManager;
  EntitiesManager entitiesManager;
  std::unique_ptr<DelaunayVoronoiGraph> delaunayVoronoiGraphPtr;
};
} // namespace model
} // namespace how

#endif // GAMEDATAMANAGER_H
