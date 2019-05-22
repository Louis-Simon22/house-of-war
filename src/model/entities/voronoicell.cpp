#include "voronoicell.h"

#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

VoronoiCell::VoronoiCell(types::point_t center,
                         std::vector<types::point_t> outlinePoints)
    : GraphEntity(Layers::TILES, center), outlinePoints(outlinePoints),
      polygon(), envelope(), outlineSegments(), tilePtr(new Tile()) {
  // Loops to get the first point again
  for (std::size_t i = 0; i < outlinePoints.size(); i++) {
    const auto &outlinePoint1 = outlinePoints[i];
    const auto &outlinePoint2 = outlinePoints[(i + 1) % outlinePoints.size()];
    bg::append(this->polygon.outer(), outlinePoint1);
    this->outlineSegments.push_back(
        types::segment_t(outlinePoint1, outlinePoint2));
  }
  // Add the first point again to close the polygon
  bg::append(this->polygon.outer(), *outlinePoints.begin());

  bg::envelope(this->polygon, this->envelope);
}

VoronoiCell::~VoronoiCell() {}

bool VoronoiCell::isTargetable() const { return true; }

bool VoronoiCell::isSelectable() const { return false; }

bool VoronoiCell::isWithinSelectionArea(types::coordinate_t posX,
                                        types::coordinate_t posY) const {
  return bg::covered_by(types::point_t(posX, posY), this->polygon);
}

const types::polygon_t &VoronoiCell::getPolygon() const {
  return this->polygon;
}

const types::box_t &VoronoiCell::getEnvelope() const { return this->envelope; }

const std::vector<types::point_t> &VoronoiCell::getOutlinePoints() const {
  return this->outlinePoints;
}

const std::vector<types::segment_t> &VoronoiCell::getOutlineSegments() const {
  return this->outlineSegments;
}

const Tile &VoronoiCell::getTile() const { return *this->tilePtr; }

Tile &VoronoiCell::getTile() { return *this->tilePtr; }

} // namespace model
} // namespace how
