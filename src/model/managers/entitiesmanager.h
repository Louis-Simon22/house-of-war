#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <memory>
#include <vector>

#include "../graphtypes.h"
#include "../entities/player.h"
#include "../utils/influencezonertree.h"

namespace how {
namespace model {
class EntitiesManager {
public:
  EntitiesManager();

public:
  void generateEntities(const types::graph_t &graph);
  types::graph_vertex_desc_t
  getVertexDescByPosition(const types::point_t &position);

private:
  void addTile(std::shared_ptr<Tile> tilePtr);

public:
  std::vector<Player> &getPlayers();
  std::vector<std::shared_ptr<Tile>> &getTilePtrs();
  InfluenceZoneRTree<std::shared_ptr<Tile>> &getTilesRtree();

private:
  std::vector<Player> players;
  std::vector<std::shared_ptr<Tile>> tilePtrs;
  InfluenceZoneRTree<std::shared_ptr<Tile>> tilesRtree;
};
} // namespace model
} // namespace how

#endif // ENTITIESMANAGER_H
