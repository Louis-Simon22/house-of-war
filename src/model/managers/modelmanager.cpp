#include "modelmanager.h"

#include "../generation/graphgenerator.h"
#include "../operations/modeliterators.h"
#include "../persistence/modeldeserializer.h"
#include "../persistence/modelserializer.h"

#include <iostream>

namespace how {
namespace model {

ModelManager::ModelManager()
    : fileName(""), worldGenerationConfig(), entitiesManager(),
      selectionManager(this->entitiesManager), iterationsCount(0) {}

void ModelManager::newModel(std::string fileName,
                            const WorldGenerationConfig &config) {
  this->worldGenerationConfig = config;
  auto graph = generateGraph(config);
  this->entitiesManager.resetEntities(graph);
  this->saveToFile(fileName);
}

void ModelManager::saveToFile() {
  writeToFile(this->fileName, serializeModel(*this));
}

void ModelManager::saveToFile(std::string fileName) {
  this->fileName = fileName;
  this->saveToFile();
}

void ModelManager::loadFromFile(std::string fileName) {
  this->fileName = fileName;
  auto deserializedModelTuple = deserializeModel(readFromFile(fileName));
  this->worldGenerationConfig = std::get<0>(deserializedModelTuple);
  auto tilePtrs = std::get<1>(deserializedModelTuple);
  auto graph = generateGraph(this->worldGenerationConfig, tilePtrs);
  this->entitiesManager.resetEntities(graph);
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
