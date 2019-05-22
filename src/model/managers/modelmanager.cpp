#include "modelmanager.h"

#include "../generation/entitygenerator.h"
#include "../generation/graphgenerator.h"

namespace how {
namespace model {

ModelManager::ModelManager() : graphEntityManagerPtr() {}

void ModelManager::newModel(WorldGenerationConfig config) {
  this->graphEntityManagerPtr = std::make_unique<GraphEntityManager>(
      generateGraph(config), config.getBoundingBox());
  types::graph_vertex_iterator_t vertexItBegin, vertexItEnd;
  ::boost::tie(vertexItBegin, vertexItEnd) =
      ::boost::vertices(this->graphEntityManagerPtr->getGraph());
  for (auto vertexIt = vertexItBegin; vertexIt != vertexItEnd; vertexIt++) {
    const auto vertexDesc = *vertexIt;
    auto voronoiCellPtr =
        this->graphEntityManagerPtr->getVoronoiCellPtrByDesc(vertexDesc);
    this->graphEntityManagerPtr->addVoronoiCell(voronoiCellPtr);
  }
  auto armyPtrs = generateArmies(this->graphEntityManagerPtr->getGraph());
  for (auto &armyPtr : armyPtrs) {
    this->graphEntityManagerPtr->addArmy(armyPtr);
  }
  auto characterPtrs =
      generateCharacters(this->graphEntityManagerPtr->getGraph());
  for (auto &characterPtr : characterPtrs) {
    this->graphEntityManagerPtr->addCharacter(characterPtr);
  }
}

GraphEntityManager *ModelManager::getGraphEntityManagerPtr() {
  return this->graphEntityManagerPtr.get();
}

} // namespace model
} // namespace how
