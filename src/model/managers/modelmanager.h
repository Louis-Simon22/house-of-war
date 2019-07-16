#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <memory>
#include <string>

#include "../generation/worldgenerationconfig.h"
#include "../persistence/savefilesmanager.h"
#include "./entitiesmanager.h"
#include "./graphmanager.h"
#include "./selectionmanager.h"

namespace how {
namespace model {
class ModelManager {
  constexpr static std::size_t LONG_ITERATION_CYCLES_COUNT = 3;

public:
  ModelManager();

public:
  void newModel(const WorldGenerationConfig &config);
  void loadModel(const WorldGenerationConfig &config,
                 std::vector<std::shared_ptr<Tile>>& tilePtrs);
  void saveToFile(std::string fileName);
  void loadFromFile(std::string fileName);
  void iterateModel();
  void onSelectionEvent(types::coordinate_t posX, types::coordinate_t posY);
  void onTargetingEvent(types::coordinate_t posX, types::coordinate_t posY);

private:
  void setEntityPositionChange(Entity *source,
                               const types::point_t &destinationPos);

public:
  const WorldGenerationConfig &getWorldGenerationConfig() const;
  const types::box_t &getWorldBounds() const;
  EntitiesManager *getEntitiesManager();
  const EntitiesManager &getEntitiesManager() const;
  const GraphManager *getDelaunayVoronoiGraph() const;
  SelectionManager *getSelectionManager();
  const SelectionManager &getSelectionManager() const;

private:
  WorldGenerationConfig worldGenerationConfig;
  EntitiesManager entitiesManager;
  SelectionManager selectionManager;
  std::unique_ptr<GraphManager> delaunayVoronoiGraphPtr;
  std::size_t iterationsCount;
};
} // namespace model
} // namespace how

#endif // MODELMANAGER_H
