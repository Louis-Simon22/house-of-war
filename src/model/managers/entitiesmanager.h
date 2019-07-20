#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <memory>
#include <vector>

#include "../entities/players/player.h"
#include "../graphtypes.h"
#include "../utils/influencezonertree.h"

namespace how {
namespace model {
class EntitiesManager {
public:
  EntitiesManager();

public:
  void addEntities(const types::graph_t &graph);
  void clearAllEntities();

private:
  void addTile(std::shared_ptr<Tile> tilePtr);

public:
  types::graph_vertex_desc_t
  getVertexDescByPosition(const types::point_t &position);
  std::vector<Player> &getPlayers();
  const std::vector<Player> &getPlayers() const;
  std::vector<std::shared_ptr<Tile>> &getTilePtrs();
  const std::vector<std::shared_ptr<Tile>> &getTilePtrs() const;
  InfluenceZoneRTree<std::shared_ptr<Tile>> &getTilesRtree();

private:
  std::vector<Player> players;
  std::vector<std::shared_ptr<Tile>> tilePtrs;
  InfluenceZoneRTree<std::shared_ptr<Tile>> tilesRtree;
};
} // namespace model
} // namespace how

#endif // ENTITIESMANAGER_H
