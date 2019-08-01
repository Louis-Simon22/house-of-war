#include "modelmanager.h"

#include "../generation/graphgenerator.h"
#include "../operations/modeliterators.h"
#include "../persistence/modeldeserializer.h"
#include "../persistence/modelserializer.h"

namespace how {
namespace model {

ModelManager::ModelManager()
    : worldGenerationConfig(), entitiesManager(),
      selectionManager(this->entitiesManager), delaunayVoronoiGraphPtr(),
      iterationsCount(0) {}

void ModelManager::newModel(const WorldGenerationConfig &config) {
  this->worldGenerationConfig = config;
  auto graph = generateGraph(config);
  this->delaunayVoronoiGraphPtr = std::make_unique<GraphManager>(graph);
  this->entitiesManager.addEntities(graph);
  this->saveToFile("greg.json");
}

void ModelManager::loadModel(const WorldGenerationConfig &config,
                             std::vector<std::shared_ptr<Tile>> &tilePtrs) {
  this->worldGenerationConfig = config;
  auto graph = generateGraph(config, tilePtrs);
  this->delaunayVoronoiGraphPtr = std::make_unique<GraphManager>(graph);
  this->entitiesManager.clearAllEntities();
  this->entitiesManager.addEntities(graph);
}

void ModelManager::saveToFile(std::string fileName) {
  serializeToFile(fileName, serializeModel(*this));
}

void ModelManager::loadFromFile(std::string fileName) {
  deserializeModel(*this, deserializeFile(fileName));
}

void ModelManager::iterateModel() {
  iterateMovement(this->entitiesManager);
  this->iterationsCount++;
  if (this->iterationsCount == LONG_ITERATION_CYCLES_COUNT) {
    this->iterationsCount = 0;
    iterateArmies(this->entitiesManager);
    iterateTiles(this->entitiesManager);
  }
}

void ModelManager::onEvent(types::coordinate_t posX, types::coordinate_t posY,
                           EventType eventType) {
  auto position = types::point_t(posX, posY);
  switch (eventType) {
  case SELECT:
    this->selectionManager.selectByPosition(position);
    break;
  case TARGET:
    this->setEntityPositionChange(this->selectionManager.getSelection(),
                                  position);
    break;
  case EDIT:
    // TODO
    break;
  }
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

const WorldGenerationConfig &ModelManager::getWorldGenerationConfig() const {
  return this->worldGenerationConfig;
}

const types::box_t &ModelManager::getWorldBounds() const {
  return this->worldGenerationConfig.boundingBox;
}

EntitiesManager *ModelManager::getEntitiesManager() {
  return &this->entitiesManager;
}

const EntitiesManager &ModelManager::getEntitiesManager() const {
  return this->entitiesManager;
}

const GraphManager *ModelManager::getDelaunayVoronoiGraph() const {
  return this->delaunayVoronoiGraphPtr.get();
}

SelectionManager *ModelManager::getSelectionManager() {
  return &this->selectionManager;
}

const SelectionManager &ModelManager::getSelectionManager() const {
  return this->selectionManager;
}

} // namespace model
} // namespace how
