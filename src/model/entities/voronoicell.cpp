#include "voronoicell.h"

#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

VoronoiCell::VoronoiCell(types::point_t position,
                         std::vector<types::point_t> outlinePoints)
    : InteractiveEntity(Layers::TILES, position), outlinePoints(outlinePoints),
      relativeOutlinePoints(outlinePoints), polygon(), envelope(),
      outlineSegments(), tilePtr(new Tile()) {
  for (std::size_t i = 0; i < outlinePoints.size(); i++) {
    const auto &outlinePoint1 = outlinePoints[i];
    // Gets the next point and wraps to get the first point again
    const auto &outlinePoint2 = outlinePoints[(i + 1) % outlinePoints.size()];
    bg::append(this->polygon.outer(), outlinePoint1);
    this->outlineSegments.push_back(
        types::segment_t(outlinePoint1, outlinePoint2));
  }
  // These points are relative to the position
  for (auto &relativeOutlinePoint : this->relativeOutlinePoints) {
    bg::subtract_point(relativeOutlinePoint, this->getPosition());
  }
  // Add the first point again to close the polygon
  bg::append(this->polygon.outer(), *outlinePoints.begin());

  bg::envelope(this->polygon, this->envelope);
}

VoronoiCell::~VoronoiCell() {}

bool VoronoiCell::isTargetable() const { return true; }

bool VoronoiCell::isSelectable() const { return true; }

const types::polygon_t &VoronoiCell::getPolygon() const {
  return this->polygon;
}

const types::box_t &VoronoiCell::getEnvelope() const { return this->envelope; }

const std::vector<types::point_t> &VoronoiCell::getOutlinePoints() const {
  return this->outlinePoints;
}

const std::vector<types::point_t> &
VoronoiCell::getRelativeOutlinePoints() const {
  return this->relativeOutlinePoints;
}

const std::vector<types::segment_t> &VoronoiCell::getOutlineSegments() const {
  return this->outlineSegments;
}

const Tile &VoronoiCell::getTile() const { return *this->tilePtr; }

Tile &VoronoiCell::getTile() { return *this->tilePtr; }

std::shared_ptr<Tile> VoronoiCell::getTilePtr() { return this->tilePtr; }

} // namespace model
} // namespace how
