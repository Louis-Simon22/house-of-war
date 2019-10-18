#include "tile.h"

namespace how {
namespace model {

Tile::Tile(types::point_t position, std::vector<types::point_t> outlinePoints)
    : VoronoiCell(position, outlinePoints), terrainType(TerrainType::DEFAULT),
      resources(0), owner(nullptr), roads() {}

Tile::~Tile() {}

bool Tile::isTargetable() const { return true; }

bool Tile::isSelectable() const { return true; }

const types::carac_t &Tile::getResources() const { return this->resources; }

void Tile::setResources(types::carac_t resources) {
  this->resources = resources;
  this->changeSignal();
}

const Player *Tile::getOwner() const { return this->owner; }

void Tile::setOwner(const Player *owner) {
  this->owner = owner;
  this->changeSignal();
}

TerrainType Tile::getTerrainType() const { return this->terrainType; }

void Tile::setTerrainType(TerrainType terrainType) {
  this->terrainType = terrainType;
  this->changeSignal();
}

const std::set<std::shared_ptr<Tile>> &Tile::getRoads() const {
  return this->roads;
}

std::vector<types::point_t> Tile::getRoadSegmentsAsPoints() const {
  auto points = std::vector<types::point_t>();
  for (const auto &tilePtr : this->roads) {
    points.push_back(this->getPosition());
    points.push_back(tilePtr->getPosition());
  }
  return points;
}

void Tile::addRoadTo(const std::shared_ptr<Tile> &tilePtr) {
  this->roads.insert(tilePtr);
  this->changeSignal();
}

} // namespace model
} // namespace how
