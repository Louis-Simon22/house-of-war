#include "modelmanager.h"

#include "../generation/graphgenerator.h"
#include "../operations/modeliterators.h"
#include "../persistence/modeldeserializer.h"
#include "../persistence/modelserializer.h"

namespace how {
namespace model {

ModelManager::ModelManager()
    : worldGenerationConfig(), entitiesManager(),
      selectionManager(this->entitiesManager), iterationsCount(0) {}

void ModelManager::newModel(const WorldGenerationConfig &config) {
  this->worldGenerationConfig = config;
  auto graph = generateGraph(config);
  this->entitiesManager.resetEntities(graph);
  this->saveToFile("greg.json");
}

void ModelManager::loadModel(const WorldGenerationConfig &config,
                             std::vector<std::shared_ptr<Tile>> &tilePtrs) {
  this->worldGenerationConfig = config;
  auto graph = generateGraph(config, tilePtrs);
  this->entitiesManager.resetEntities(graph);
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

void ModelManager::onEvent(const ModelEvent &modelEvent) {
  modelEvent.applyEvent(this->entitiesManager, this->selectionManager);
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

SelectionManager *ModelManager::getSelectionManager() {
  return &this->selectionManager;
}

const SelectionManager &ModelManager::getSelectionManager() const {
  return this->selectionManager;
}

} // namespace model
} // namespace how
