#include "modelmanager.h"

#include "../generation/entitygenerator.h"
#include "../generation/worldgenerator.h"

namespace how {
namespace model {

ModelManager::ModelManager() : graphEntityManager(), worldManagerPtr() {}

void ModelManager::newModel(WorldGenerationConfig config) {
  this->worldManagerPtr.reset(generateWorld(config));
  types::graph_vertex_iterator_t vertexItBegin, vertexItEnd;
  ::boost::tie(vertexItBegin, vertexItEnd) =
      ::boost::vertices(this->worldManagerPtr->getGraph());
  for (auto vertexIt = vertexItBegin; vertexIt != vertexItEnd; vertexIt++) {
    const auto vertexDesc = *vertexIt;
    model::VoronoiCell &voronoiCell =
        this->worldManagerPtr->getVoronoiCellByDesc(vertexDesc);
    this->graphEntityManager.addGraphEntity(&voronoiCell);
  }
  this->armies = generateArmies(this->worldManagerPtr->getGraph());
  for (auto &army : armies) {
    this->graphEntityManager.addGraphEntity(&army);
  }
  this->characters = generateCharacters(this->worldManagerPtr->getGraph());
  for (auto &character : characters) {
    this->graphEntityManager.addGraphEntity(&character);
  }
}

WorldManager *ModelManager::getWorldManagerPtr() const {
  return this->worldManagerPtr.get();
}

GraphEntityManager &ModelManager::getGraphEntityManager() {
  return this->graphEntityManager;
}

const std::vector<Army> ModelManager::getArmies() const { return this->armies; }

const std::vector<Character> ModelManager::getCharacters() const {
  return this->characters;
}

} // namespace model
} // namespace how
