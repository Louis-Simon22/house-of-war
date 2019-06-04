#include "modelmanager.h"

#include "../generation/graphgenerator.h"
#include "../operations/armiesiterator.h"
#include "../operations/tilesiterator.h"

namespace how {
namespace model {

ModelManager::ModelManager()
    : entityChangeManager(), entitiesManager(), delaunayVoronoiGraphPtr() {}

void ModelManager::newModel(const WorldGenerationConfig &config) {
  auto graphAndSpatialIndexTree = generateGraph(config);
  auto &graph = std::get<0>(graphAndSpatialIndexTree);
  auto &spatialIndexTree = std::get<1>(graphAndSpatialIndexTree);
  this->delaunayVoronoiGraphPtr = std::make_unique<DelaunayVoronoiGraph>(
      graph, spatialIndexTree, config.getBoundingBox());
  this->entitiesManager.generateEntities(graph);
}

void ModelManager::iterateModel() {
  iterateTiles(this->entitiesManager);
  iterateArmies(this->entitiesManager, this->delaunayVoronoiGraphPtr.get());
  this->entityChangeManager.iterateAllEntityChanges();
}

void ModelManager::addGraphEntityPositionChange(Entity *source,
                                                const Entity *destination) {
  auto destinations = this->delaunayVoronoiGraphPtr->getDestinationsBetween(
      source, destination);
  this->entityChangeManager.addGraphEntityPositionChange(source, destinations);
}

EntityChangeManager *ModelManager::getEntityChangeManager() {
  return &this->entityChangeManager;
}

EntitiesManager *ModelManager::getEntitiesManager() {
  return &this->entitiesManager;
}

const DelaunayVoronoiGraph *ModelManager::getDelaunayVoronoiGraphPtr() const {
  return this->delaunayVoronoiGraphPtr.get();
}

} // namespace model
} // namespace how
