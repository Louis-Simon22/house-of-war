#include "modelmanager.h"

#include "../generation/graphgenerator.h"
#include "../operations/modeliterators.h"

namespace how {
namespace model {

ModelManager::ModelManager()
    : entitiesManager(), selectionManager(this->entitiesManager),
      delaunayVoronoiGraphPtr(), iterationsCount(0) {}

void ModelManager::newModel(const WorldGenerationConfig &config) {
  auto graph = generateGraph(config);
  this->delaunayVoronoiGraphPtr =
      std::make_unique<GraphManager>(graph, config.getBoundingBox());
  this->entitiesManager.generateEntities(graph);
}

void ModelManager::iterateModel() {
  iterateMovement(this->entitiesManager);
  if (this->iterationsCount == LONG_ITERATION_CYCLES_COUNT) {
    this->iterationsCount = 0;
    iterateTiles(this->entitiesManager);
    iterateArmies(this->entitiesManager);
  } else {
    this->iterationsCount++;
  }
}

void ModelManager::onSelectionEvent(types::coordinate_t posX,
                                    types::coordinate_t posY) {
  auto position = types::point_t(posX, posY);
  this->selectionManager.selectByPosition(position);
}

void ModelManager::onTargetingEvent(types::coordinate_t posX,
                                    types::coordinate_t posY) {
  auto position = types::point_t(posX, posY);
  this->setEntityPositionChange(this->selectionManager.getSelection(),
                                position);
}

void ModelManager::setEntityPositionChange(
    Entity *source, const types::point_t &destinationPos) {
  const auto &sourceVertexDesc = this->entitiesManager.getVertexDescByPosition(
      source->getAbsolutePosition());
  const auto &destinationVertexDesc =
      this->entitiesManager.getVertexDescByPosition(destinationPos);
  auto destinations = this->delaunayVoronoiGraphPtr->getDestinationsBetween(
      sourceVertexDesc, destinationVertexDesc);
  source->setEntityPositionChange(
      new EntityPositionChange(source, destinations));
}

EntitiesManager *ModelManager::getEntitiesManager() {
  return &this->entitiesManager;
}

const GraphManager *ModelManager::getDelaunayVoronoiGraphPtr() const {
  return this->delaunayVoronoiGraphPtr.get();
}

SelectionManager *ModelManager::getSelectionManager() {
  return &this->selectionManager;
}

} // namespace model
} // namespace how
