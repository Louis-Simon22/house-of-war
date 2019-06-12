#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <memory>

#include "../generation/worldgenerationconfig.h"
#include "./entitiesmanager.h"
#include "./entitychangemanager.h"
#include "./graphmanager.h"
#include "./selectionmanager.h"

namespace how {
namespace model {
class ModelManager {
public:
  ModelManager();

public:
  void newModel(const WorldGenerationConfig &config);
  void iterateModel();
  void onSelectionEvent(types::coordinate_t posX, types::coordinate_t posY);
  void onTargetingEvent(types::coordinate_t posX, types::coordinate_t posY);

private:
  void addGraphEntityPositionChange(Entity *source,
                                    const types::point_t &destinationPos);

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

#endif // MODELMANAGER_H
