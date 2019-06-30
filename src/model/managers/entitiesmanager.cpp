#include "entitiesmanager.h"

#include "../generation/playergenerator.h"

namespace how {
namespace model {

EntitiesManager::EntitiesManager() : players(), tilePtrs() {}

void EntitiesManager::generateEntities(const types::graph_t &graph) {
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

std::vector<Player> &EntitiesManager::getPlayers() { return this->players; }

types::graph_vertex_desc_t
EntitiesManager::getVertexDescByPosition(const types::point_t &position) {
  const auto &vertexDesc = this->tilesRtree.getValuesByPosition(position);
  return vertexDesc[0]->getVertexDesc();
}

std::vector<std::shared_ptr<Tile>> &EntitiesManager::getTilePtrs() {
  return this->tilePtrs;
}

InfluenceZoneRTree<std::shared_ptr<Tile>> &EntitiesManager::getTilesRtree() {
  return this->tilesRtree;
}

} // namespace model
} // namespace how
