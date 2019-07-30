#ifndef TILE_H
#define TILE_H

#include "../modeltypes.h"
#include "./player.h"
#include "./terraintype.h"
#include "./voronoicell.h"

namespace how {
namespace model {
class Tile : public VoronoiCell {
public:
  Tile(types::point_t position, std::vector<types::point_t> outlinePoints);
  ~Tile() override;

public:
  bool isTargetable() const override;
  bool isSelectable() const override;

public:
  const types::carac_t &getResources() const;
  void setResources(types::carac_t resources);
  const Player *getOwner() const;
  void setOwner(const Player *owner);
  TerrainType getTerrainType() const;
  void setTerrain(TerrainType terrainType);

private:
  TerrainType terrainType;
  types::carac_t resources;
  const Player *owner;
};
} // namespace model
} // namespace how

#endif // TILE_H
