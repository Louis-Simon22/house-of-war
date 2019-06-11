#include "entitiesmanager.h"

#include "../generation/entitygenerator.h"

namespace how {
namespace model {

EntitiesManager::EntitiesManager()
    : armyPtrs(), characterPtrs(), voronoiCellPtrs() {}

void EntitiesManager::generateEntities(const types::graph_t &graph) {
  auto armyPtrs = generateArmies(graph);
  for (auto &armyPtr : armyPtrs) {
    this->addArmy(armyPtr);
  }
  auto characterPtrs = generateCharacters(graph);
  for (auto &characterPtr : characterPtrs) {
    this->addCharacter(characterPtr);
  }
  types::graph_vertex_iterator_t vertexBegin, vertexEnd;
  ::boost::tie(vertexBegin, vertexEnd) = ::boost::vertices(graph);
  for (auto vertexIt = vertexBegin; vertexIt != vertexEnd; vertexIt++) {
    this->addVoronoiCell(graph[*vertexIt]);
  }
}

void EntitiesManager::addArmy(std::shared_ptr<Army> armyPtr) {
  this->armyPtrs.push_back(armyPtr);
}

void EntitiesManager::addCharacter(std::shared_ptr<Character> characterPtr) {
  this->characterPtrs.push_back(characterPtr);
}

void EntitiesManager::addVoronoiCell(
    std::shared_ptr<VoronoiCell> voronoiCellPtr) {
  this->voronoiCellPtrs.push_back(voronoiCellPtr);
}

std::vector<std::shared_ptr<Army>> &EntitiesManager::getArmyPtrs() {
  return this->armyPtrs;
}

std::vector<std::shared_ptr<Character>> &EntitiesManager::getCharacterPtrs() {
  return this->characterPtrs;
}

std::vector<std::shared_ptr<VoronoiCell>> &
EntitiesManager::getVoronoiCellPtrs() {
  return this->voronoiCellPtrs;
}

} // namespace model
} // namespace how
