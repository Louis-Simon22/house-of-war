#include "tile.h"

namespace how {
namespace model {

Tile::Tile() : height() {}

Tile::~Tile() {}

void Tile::setHeight(charac_t height) { this->height = height; }

const charac_t &Tile::getHeight() const { return this->height; }

charac_t &Tile::getHeight() { return this->height; }

} // namespace model
} // namespace how
