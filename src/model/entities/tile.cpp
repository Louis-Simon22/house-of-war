#include "tile.h"

namespace how {
namespace model {

Tile::Tile() : altitude() {}

Tile::~Tile() {}

void Tile::setAltitude(charac_t altitude) { this->altitude = altitude; }

const charac_t &Tile::getAltitude() const { return this->altitude; }

charac_t &Tile::getAltitude() { return this->altitude; }

} // namespace model
} // namespace how
