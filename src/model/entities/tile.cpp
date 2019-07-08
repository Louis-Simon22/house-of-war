#include "tile.h"

namespace how {
namespace model {

Tile::Tile(types::point_t position, std::vector<types::point_t> outlinePoints)
    : VoronoiCell(position, outlinePoints), altitude(0), resources(0),
      owner(nullptr) {}

Tile::~Tile() {}

bool Tile::isTargetable() const { return true; }

bool Tile::isSelectable() const { return true; }

const charac_t &Tile::getAltitude() const { return this->altitude; }

charac_t &Tile::getAltitude() { return this->altitude; }

void Tile::setAltitude(charac_t altitude) { this->altitude = altitude; }

charac_t Tile::getResources() const { return this->resources; }

charac_t &Tile::getResources() { return this->resources; }

void Tile::setResources(charac_t resources) {
  this->resources = resources;
  this->changedSignal();
}

const Player *Tile::getOwner() const { return this->owner; }

void Tile::setOwner(const Player *owner) { this->owner = owner; }

} // namespace model
} // namespace how
