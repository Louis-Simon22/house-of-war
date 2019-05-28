#ifndef TILE_H
#define TILE_H

#include "../modeltypes.h"
#include "./graphentity.h"

namespace how {
namespace model {
namespace {
using charac_t = types::charac_t;
} // namespace

class Tile {
public:
  Tile();
  ~Tile();

public:
  const charac_t &getAltitude() const;
  charac_t &getAltitude();
  void setAltitude(charac_t altitude);
  const charac_t &getResources() const;
  charac_t &getResources();
  void setResources(charac_t resources);

private:
  charac_t altitude;
  charac_t resources;
};
} // namespace model
} // namespace how

#endif // TILE_H
