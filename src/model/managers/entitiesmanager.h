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
  void resetEntities(types::graph_t &graph);

private:
  void clearAllEntities();
  void addTilesFromGraph();
  void addTile(std::shared_ptr<Tile> tilePtr);

public:
  const types::graph_t &getGraph();
  std::shared_ptr<Tile> getTilePtrByPosition(const types::point_t &position);
  types::graph_vertex_desc_t
  getVertexDescByPosition(const types::point_t &position);
  const std::vector<types::segment_t> &getUniqueVoronoiSegments() const;
  const std::vector<types::segment_t> &getUniqueDelaunaySegments() const;
  std::vector<Player> &getPlayers();
  const std::vector<Player> &getPlayers() const;
  std::vector<std::shared_ptr<Tile>> &getTilePtrs();
  const std::vector<std::shared_ptr<Tile>> &getTilePtrs() const;
  InfluenceZoneRTree<std::shared_ptr<Tile>> &getTilesRtree();

private:
  types::graph_t graph;
  std::vector<types::segment_t> uniqueVoronoiSegments;
  std::vector<types::segment_t> uniqueDelaunaySegments;
  std::vector<Player> players;
  std::vector<std::shared_ptr<Tile>> tilePtrs;
  InfluenceZoneRTree<std::shared_ptr<Tile>> tilesRtree;
};
} // namespace model
} // namespace how

#endif // ENTITIESMANAGER_H
