#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <memory>
#include <vector>

#include "../entities/players/player.h"
#include "../entities/terrain/tile.h"
#include "../graphtypes.h"
#include "../utils/influencezonertree.h"

namespace how {
namespace model {
class EntitiesManager {
public:
  EntitiesManager();

public:
  void resetEntities(types::graph_t &graph);

private:
  void clearAllEntities(types::graph_t &graph);
  void addTilesFromGraph();
  void addTile(std::shared_ptr<Tile> tilePtr);

public:
  const types::graph_t &getGraph();
  const std::vector<types::segment_t> &getUniqueVoronoiSegments() const;
  const std::vector<types::segment_t> &getUniqueDelaunaySegments() const;
  std::vector<Player> &getPlayers();
  const std::vector<Player> &getPlayers() const;
  std::vector<std::shared_ptr<Tile>> &getTilePtrs();
  const std::vector<std::shared_ptr<Tile>> &getTilePtrs() const;
  InfluenceZoneRTree<std::shared_ptr<Tile>> &getTilesRTree();

private:
  types::graph_t graph;
  std::vector<types::segment_t> uniqueVoronoiSegments;
  std::vector<types::segment_t> uniqueDelaunaySegments;
  std::vector<Player> players;
  std::vector<std::shared_ptr<Tile>> tilePtrs;
  InfluenceZoneRTree<std::shared_ptr<Tile>> tilesRTree;
};
} // namespace model
} // namespace how

#endif // ENTITIESMANAGER_H
