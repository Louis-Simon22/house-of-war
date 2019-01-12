#include "modelfacade.h"

namespace how {
namespace model {
ModelFacade::ModelFacade() : worldData(std::unique_ptr<WorldData>()) {}

// TODO safeguards around these functions in case the worldData is not
// instantiated yet ??
const types::box_t ModelFacade::getWorldBounds() const {
  return this->worldData->getBounds();
}

const std::vector<types::point_t> *ModelFacade::getPointsList() const {
  return this->worldData->getPointsList();
}

const types::vd_t *ModelFacade::getVoronoiDiagram() const {
  return this->worldData->getVoronoiDiagram();
}

void ModelFacade::generateNewWorld(const types::WorldGenerationConfig &config) {
  const auto &worldBuilder = ::how::model::WorldBuilder(config);
  auto worldData = worldBuilder.build();
  this->worldData.reset(worldData);
}
} // namespace model
} // namespace how
