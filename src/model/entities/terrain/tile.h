#ifndef TILE_H
#define TILE_H

#include "../modeltypes.h"
#include "./player.h"
#include "./terrain.h"
#include "./terraincharacvalue.h"
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
  void setAltitude(TerrainCharacValue altitude);
  const types::charac_t &getResources() const;
  void setResources(charac_t resources);
  const Player *getOwner() const;
  void setOwner(const Player *owner);

private:
  // TODO see notebook
  TerrainCharacValue altitude;
  types::charac_t altitude;
  types::charac_t resources;
  const Player *owner;
};
} // namespace model
} // namespace how

#endif // TILE_H
