#include "tile.h"

namespace how {
namespace model {

Tile::Tile(types::point_t position, std::vector<types::point_t> outlinePoints)
    : VoronoiCell(position, outlinePoints), terrainType(TerrainType::DEFAULT),
      resources(0), owner(nullptr) {}

Tile::~Tile() {}

bool Tile::isTargetable() const { return true; }

bool Tile::isSelectable() const { return true; }

const types::carac_t &Tile::getResources() const { return this->resources; }

void Tile::setResources(types::carac_t resources) {
  this->resources = resources;
  this->changedSignal();
}

const Player *Tile::getOwner() const { return this->owner; }

void Tile::setOwner(const Player *owner) {
  this->owner = owner;
  this->changedSignal();
}

TerrainType Tile::getTerrainType() const { return this->terrainType; }

void Tile::setTerrainType(TerrainType terrainType) {
  this->terrainType = terrainType;
  this->changedSignal();
}

} // namespace model
} // namespace how
