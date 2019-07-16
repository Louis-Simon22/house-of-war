#include "entitiesmanager.h"

#include "../generation/playergenerator.h"

namespace how {
namespace model {

EntitiesManager::EntitiesManager() : players(), tilePtrs() {}

void EntitiesManager::addEntities(const types::graph_t &graph) {
  // TODO move this to another method maybe
  this->players.push_back(generatePlayer(graph));
  types::graph_vertex_iterator_t vertexBegin, vertexEnd;
  ::boost::tie(vertexBegin, vertexEnd) = ::boost::vertices(graph);
  for (auto vertexIt = vertexBegin; vertexIt != vertexEnd; vertexIt++) {
    this->addTile(graph[*vertexIt]);
  }
}

void EntitiesManager::addTile(std::shared_ptr<Tile> tilePtr) {
  this->tilePtrs.push_back(tilePtr);
  this->tilesRtree.addValue(tilePtr->getPolygonInfluenceZone(), tilePtr);
}

void EntitiesManager::clearAllEntities() {
  this->players.clear();
  this->tilePtrs.clear();
  this->tilesRtree.clearAllValues();
}

types::graph_vertex_desc_t
EntitiesManager::getVertexDescByPosition(const types::point_t &position) {
  const auto &vertexDesc = this->tilesRtree.getValuesByPosition(position);
  return vertexDesc[0]->getVertexDesc();
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

InfluenceZoneRTree<std::shared_ptr<Tile>> &EntitiesManager::getTilesRtree() {
  return this->tilesRtree;
}

} // namespace model
} // namespace how
