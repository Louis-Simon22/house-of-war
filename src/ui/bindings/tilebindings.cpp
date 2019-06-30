#include "tilebindings.h"

namespace how {
namespace ui {

TileBindings::TileBindings() : tile(nullptr) {}

TileBindings::~TileBindings() {}

void TileBindings::bindTile(model::Tile *tile) {
  this->tile = tile;
  this->bindEntity(tile);
}

types::carac_t TileBindings::getAltitude() const {
  return this->tile ? this->tile->getAltitude() : 0;
}

types::carac_t TileBindings::getResources() const {
  return this->tile ? this->tile->getResources() : 0;
}

} // namespace ui
} // namespace how
