#include "tile.h"

namespace how {
namespace model {

Tile::Tile() : altitude(), resources() {}

Tile::~Tile() {}

const charac_t &Tile::getAltitude() const { return this->altitude; }

charac_t &Tile::getAltitude() { return this->altitude; }

void Tile::setAltitude(charac_t altitude) { this->altitude = altitude; }

const charac_t &Tile::getResources() const { return this->resources; }

charac_t &Tile::getResources() { return this->resources; }

void Tile::setResources(charac_t resources) { this->resources = resources; }

} // namespace model
} // namespace how
