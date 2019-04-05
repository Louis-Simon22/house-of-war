#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H

#include <memory>

#include "./characters/characterdata.h"
#include "./characters/charactergeneration/charactergenerator.h"
#include "./entities/movement/movementmanager.h"
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
  MovementManager *getMovementManagerPtr() const;

private:
  std::unique_ptr<MovementManager> movementManagerPtr;
  std::unique_ptr<WorldData> worldDataPtr;
  std::unique_ptr<CharacterData> characterDataPtr;
};
} // namespace model
} // namespace how

#endif // GAMEDATAMANAGER_H
