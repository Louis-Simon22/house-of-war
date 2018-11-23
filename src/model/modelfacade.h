#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <boost/geometry/geometries/box.hpp>
#include <memory>
#include "modeltypes.h"
#include "world/worlddata.h"
#include "world/worldgeneration/worldbuilder.h"

namespace how {
namespace model {
namespace bg = ::boost::geometry;
class ModelFacade {
 public:
  ModelFacade();
  const types::box_t getWorldBounds() const;
  const std::vector<types::point_t>& getPointsList() const;
  void generateNewWorld(types::WorldGenerationConfig config);

 private:
  std::unique_ptr<WorldData> worldData;
};
}  // namespace model
}  // namespace how
#endif
