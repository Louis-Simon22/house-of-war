#ifndef TILE_H
#define TILE_H

#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
using charac_t = types::characteristics_t;
}

class Tile {
public:
  Tile();
  ~Tile();

public:
  const charac_t &getHeight() const;
  charac_t &getHeight();
  void setHeight(charac_t height);

private:
  charac_t height;
};
} // namespace model
} // namespace how

#endif // TILE_H
