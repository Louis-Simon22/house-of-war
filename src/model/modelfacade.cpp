#include "modelfacade.h"

namespace how {
namespace model {
ModelFacade::ModelFacade() : worldData(std::unique_ptr<WorldData>()) {}

const types::box_t ModelFacade::getWorldBounds() const {
  return this->worldData->getBounds();
}

const std::vector<types::point_t>& ModelFacade::getPointsList() const {
  return this->worldData->getPointsList();
}

void ModelFacade::generateNewWorld(types::WorldGenerationConfig config) {
  auto worldData = ::how::model::WorldBuilder(config).build();
  this->worldData.reset(worldData);
}
}  // namespace model
}  // namespace how
