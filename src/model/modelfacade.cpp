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

const std::vector<types::segment_t> *ModelFacade::getOutlineSegments() const {
  return this->worldData->getOutlineSegments();
}

const std::vector<VoronoiCell> *ModelFacade::getVoronoiCells() const {
  return this->worldData->getVoronoiCells();
}

void ModelFacade::generateNewWorld(const types::WorldGenerationConfig &config) {
  auto* worldData = buildWorld(config);
  this->worldData.reset(worldData);
}
} // namespace model
} // namespace how
