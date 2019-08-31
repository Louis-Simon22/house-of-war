#include "entitiesmanager.h"

#include "../generation/playergenerator.h"
#include "../operations/graphoperations.h"

namespace how {
namespace model {

EntitiesManager::EntitiesManager() : players(), tilePtrs() {}

void EntitiesManager::resetEntities(types::graph_t &graph) {
  this->clearAllEntities(graph);
  this->addTilesFromGraph();
  this->uniqueVoronoiSegments = extractUniqueVoronoiSegments(graph);
  this->uniqueDelaunaySegments = extractUniqueDelaunaySegments(graph);
}

void EntitiesManager::clearAllEntities(types::graph_t &graph) {
  this->graph = graph;
  this->uniqueVoronoiSegments.clear();
  this->uniqueDelaunaySegments.clear();
  this->players.clear();
  this->tilePtrs.clear();
  this->tilesRTree.clearAllValues();
}

void EntitiesManager::addTilesFromGraph() {
  // TODO move this (maybe as parameter to resetEntities)
  this->players.push_back(generatePlayer(this->graph));
  types::graph_vertex_iterator_t vertexBegin, vertexEnd;
  ::boost::tie(vertexBegin, vertexEnd) = ::boost::vertices(this->graph);
  for (auto vertexIt = vertexBegin; vertexIt != vertexEnd; vertexIt++) {
    this->addTile(this->graph[*vertexIt]);
  }
}

void EntitiesManager::addTile(std::shared_ptr<Tile> tilePtr) {
  this->tilePtrs.push_back(tilePtr);
  this->tilesRTree.addValue(tilePtr->getPolygonInfluenceZone(), tilePtr);
}

const types::graph_t &EntitiesManager::getGraph() { return this->graph; }

const std::vector<types::segment_t> &
EntitiesManager::getUniqueVoronoiSegments() const {
  return this->uniqueVoronoiSegments;
}

const std::vector<types::segment_t> &
EntitiesManager::getUniqueDelaunaySegments() const {
  return this->uniqueDelaunaySegments;
}

std::vector<Player> &EntitiesManager::getPlayers() { return this->players; }

const std::vector<Player> &EntitiesManager::getPlayers() const {
  return this->players;
}

std::vector<std::shared_ptr<Tile>> &EntitiesManager::getTilePtrs() {
  return this->tilePtrs;
}

const std::vector<std::shared_ptr<Tile>> &EntitiesManager::getTilePtrs() const {
  return this->tilePtrs;
}

InfluenceZoneRTree<std::shared_ptr<Tile>> &EntitiesManager::getTilesRTree() {
  return this->tilesRTree;
}

} // namespace model
} // namespace how
