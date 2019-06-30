#ifndef TILE_H
#define TILE_H

#include "../modeltypes.h"
#include "./voronoicell.h"

namespace how {
namespace model {
namespace {
using charac_t = types::carac_t;
} // namespace

class Tile : public VoronoiCell {
public:
  Tile(types::point_t position, std::vector<types::point_t> outlinePoints);
  ~Tile() override;

public:
  bool isTargetable() const override;
  bool isSelectable() const override;

public:
  const charac_t &getAltitude() const;
  charac_t &getAltitude();
  void setAltitude(charac_t altitude);
  charac_t getResources() const;
  charac_t &getResources();
  void setResources(charac_t resources);

private:
  charac_t altitude;
  charac_t resources;
};
} // namespace model
} // namespace how

#endif // TILE_H
