#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../model/world/worlddata.h"
#include "../model/world/worldgeneration/worldbuilder.h"
#include <memory>
#include <vector>

namespace how {
namespace control {
namespace {
namespace bg = ::boost::geometry;
}
class GameManager {
  using WorldData = ::how::model::WorldData;
  using WorldGenerationConfig = ::how::model::types::WorldGenerationConfig;

public:
  explicit GameManager();

  void generateNewWorld(const WorldGenerationConfig &config);

  const std::vector<::how::model::types::point_t> *getPointsList() const;
  const std::vector<::how::model::types::segment_t> *getOutlineSegments() const;
  const ::how::model::types::box_t getWorldBounds() const;

private:
  std::unique_ptr<WorldData> worldDataPtr;
};
} // namespace control
} // namespace how
#endif
