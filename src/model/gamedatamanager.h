#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H

#include <memory>

#include "./entities/characters/characterdata.h"
#include "./entities/characters/charactergeneration/charactergenerator.h"
#include "./entities/entitychangemanager.h"
#include "./modeltypes.h"
#include "./world/worlddata.h"
#include "./world/worldgeneration/worldgenerator.h"

namespace how {
namespace model {
class GameDataManager {
public:
  GameDataManager();

public:
  void newGame(types::WorldGenerationConfig config);
  WorldData *getWorldDataPtr() const;
  CharacterData *getCharacterDataPtr() const;
  EntityChangeManager *getEntityChangeManangerPtr() const;

private:
  std::unique_ptr<EntityChangeManager> entityChangeManangerPtr;
  std::unique_ptr<WorldData> worldDataPtr;
  std::unique_ptr<CharacterData> characterDataPtr;
};
} // namespace model
} // namespace how

#endif // GAMEDATAMANAGER_H
