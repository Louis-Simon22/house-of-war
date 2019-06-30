#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <memory>

#include "../generation/worldgenerationconfig.h"
#include "./entitiesmanager.h"
#include "./graphmanager.h"
#include "./selectionmanager.h"

namespace how {
namespace model {
class ModelManager {
  constexpr static std::size_t LONG_ITERATION_CYCLES_COUNT = 0;

public:
  ModelManager();

public:
  void newModel(const WorldGenerationConfig &config);
  void iterateModel();
  void onSelectionEvent(types::coordinate_t posX, types::coordinate_t posY);
  void onTargetingEvent(types::coordinate_t posX, types::coordinate_t posY);

private:
  void setEntityPositionChange(Entity *source,
                               const types::point_t &destinationPos);

public:
  EntitiesManager *getEntitiesManager();
  const GraphManager *getDelaunayVoronoiGraphPtr() const;
  SelectionManager *getSelectionManager();

private:
  EntitiesManager entitiesManager;
  SelectionManager selectionManager;
  std::unique_ptr<GraphManager> delaunayVoronoiGraphPtr;
  std::size_t iterationsCount;
};
} // namespace model
} // namespace how

#endif // MODELMANAGER_H
