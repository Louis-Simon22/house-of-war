#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <string>

#include "../events/modelevent.h"
#include "../generation/worldgenerationconfig.h"
#include "./entitiesmanager.h"
#include "./selectionmanager.h"

namespace how {
namespace model {
class ModelManager {
  constexpr static std::size_t LONG_ITERATION_CYCLES_COUNT = 3;

public:
  ModelManager();

public:
  void newModel(const std::string & fileName, const WorldGenerationConfig &config);
  void saveToFile(const std::string & fileName);
  void saveToFile();
  void loadFromFile(const std::string &fileName);
  void iterateModel();
  void onEvent(const ModelEvent &modelEvent);

public:
  const WorldGenerationConfig &getWorldGenerationConfig() const;
  const types::box_t &getWorldBounds() const;
  EntitiesManager *getEntitiesManager();
  const EntitiesManager &getEntitiesManager() const;
  SelectionManager *getSelectionManager();
  const SelectionManager &getSelectionManager() const;

private:
  std::string fileName;
  WorldGenerationConfig worldGenerationConfig;
  EntitiesManager entitiesManager;
  SelectionManager selectionManager;
  std::size_t iterationsCount;
};
} // namespace model
} // namespace how

#endif // MODELMANAGER_H
