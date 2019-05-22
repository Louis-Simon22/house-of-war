#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H

#include <memory>

#include "../generation/worldgenerationconfig.h"
#include "./graphentitymanager.h"

namespace how {
namespace model {
class ModelManager {
public:
  ModelManager();

public:
  void newModel(WorldGenerationConfig config);

public:
  GraphEntityManager *getGraphEntityManagerPtr();

private:
  std::unique_ptr<GraphEntityManager> graphEntityManagerPtr;
};
} // namespace model
} // namespace how

#endif // GAMEDATAMANAGER_H
