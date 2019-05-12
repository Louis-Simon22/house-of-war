#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H

#include <memory>

#include "../generation/worldgenerationconfig.h"
#include "./graphentitymanager.h"
#include "./worldmanager.h"

namespace how {
namespace model {
class ModelManager {
public:
  ModelManager();

public:
  void newModel(WorldGenerationConfig config);

public:
  GraphEntityManager &getGraphEntityManager();
  const std::vector<Army> getArmies() const;
  const std::vector<Character> getCharacters() const;
  WorldManager *getWorldManagerPtr() const;

private:
  GraphEntityManager graphEntityManager;
  std::vector<Army> armies;
  std::vector<Character> characters;
  std::unique_ptr<WorldManager> worldManagerPtr;
};
} // namespace model
} // namespace how

#endif // GAMEDATAMANAGER_H
