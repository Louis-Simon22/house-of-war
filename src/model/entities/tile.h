#ifndef TILE_H
#define TILE_H

#include "../modeltypes.h"
#include "./graphentity.h"

namespace how {
namespace model {
namespace {
using charac_t = types::characteristics_t;
} // namespace

class Tile {
public:
  Tile();
  ~Tile();

public:
  const charac_t &getAltitude() const;
  charac_t &getAltitude();
  void setAltitude(charac_t altitude);

private:
  charac_t altitude;
};
} // namespace model
} // namespace how

#endif // TILE_H
