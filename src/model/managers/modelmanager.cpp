#include "modelmanager.h"

#include "../generation/graphgenerator.h"
#include "../operations/armiesiterator.h"
#include "../operations/tilesiterator.h"

namespace how {
namespace model {

ModelManager::ModelManager()
    : entityChangeManager(), entitiesManager(), selectionManager(),
      delaunayVoronoiGraphPtr() {}

void ModelManager::newModel(const WorldGenerationConfig &config) {
  auto graph = generateGraph(config);
  this->delaunayVoronoiGraphPtr =
      std::make_unique<GraphManager>(graph, config.getBoundingBox());
  this->entitiesManager.generateEntities(graph);
}

void ModelManager::iterateModel() {
  iterateTiles(this->entitiesManager);
  iterateArmies(this->entitiesManager, this->delaunayVoronoiGraphPtr.get());
  this->entityChangeManager.iterateAllEntityChanges();
}

void ModelManager::onSelectionEvent(types::coordinate_t posX,
                                    types::coordinate_t posY) {
  auto position = types::point_t(posX, posY);
  const auto &armies =
      this->entitiesManager.getArmiesRtree().getValuesByPosition(position);
  if (armies.size() > 0) {
    this->selectionManager.setSelection(armies[0].get());
  }
}

void ModelManager::onTargetingEvent(types::coordinate_t posX,
                                    types::coordinate_t posY) {
  auto position = types::point_t(posX, posY);
  this->addGraphEntityPositionChange(this->selectionManager.getSelection(),
                                     position);
}

void ModelManager::addGraphEntityPositionChange(
    Entity *source, const types::point_t &destinationPos) {
  const auto &destinationVertexDesc =
      this->entitiesManager.getVertexDescByPosition(destinationPos);
  const auto &sourceVertexDesc = this->entitiesManager.getVertexDescByPosition(
      source->getAbsolutePosition());
  auto destinations = this->delaunayVoronoiGraphPtr->getDestinationsBetween(
      destinationVertexDesc, sourceVertexDesc);
  this->entityChangeManager.addGraphEntityPositionChange(source, destinations);
}

EntityChangeManager *ModelManager::getEntityChangeManager() {
  return &this->entityChangeManager;
}

EntitiesManager *ModelManager::getEntitiesManager() {
  return &this->entitiesManager;
}

const GraphManager *ModelManager::getDelaunayVoronoiGraphPtr() const {
  return this->delaunayVoronoiGraphPtr.get();
}

} // namespace model
} // namespace how
