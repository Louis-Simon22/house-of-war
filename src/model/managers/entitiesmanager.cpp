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
  this->armiesRtree.addValue(armyPtr->getSelectionZonePtr(), armyPtr);
}

void EntitiesManager::addCharacter(std::shared_ptr<Character> characterPtr) {
  this->characterPtrs.push_back(characterPtr);
}

void EntitiesManager::addVoronoiCell(
    std::shared_ptr<VoronoiCell> voronoiCellPtr) {
  this->voronoiCellPtrs.push_back(voronoiCellPtr);
  this->voronoiCellsRtree.addValue(voronoiCellPtr->getEnvelopeZonePtr(),
                                   voronoiCellPtr);
}

types::graph_vertex_desc_t
EntitiesManager::getVertexDescByPosition(const types::point_t &position) {
  const auto &vertexDesc =
      this->voronoiCellsRtree.getValuesByPosition(position);
  return vertexDesc[0]->getVertexDesc();
}

std::vector<std::shared_ptr<Army>> &EntitiesManager::getArmyPtrs() {
  return this->armyPtrs;
}

InfluenceZoneRTree<std::shared_ptr<Army>> &EntitiesManager::getArmiesRtree() {
  return this->armiesRtree;
}

std::vector<std::shared_ptr<Character>> &EntitiesManager::getCharacterPtrs() {
  return this->characterPtrs;
}

InfluenceZoneRTree<std::shared_ptr<Character>> &
EntitiesManager::getCharactersRtree() {
  return this->charactersRtree;
}

std::vector<std::shared_ptr<VoronoiCell>> &
EntitiesManager::getVoronoiCellPtrs() {
  return this->voronoiCellPtrs;
}

InfluenceZoneRTree<std::shared_ptr<VoronoiCell>> &
EntitiesManager::getVoronoiCellsRtree() {
  return this->voronoiCellsRtree;
}

} // namespace model
} // namespace how
