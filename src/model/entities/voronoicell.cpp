#include "voronoicell.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

VoronoiCell::VoronoiCell()
    : GraphEntity(Layers::TILES_LAYER, types::point_t()) {}

VoronoiCell::VoronoiCell(types::box_t envelope, types::point_t center,
                         types::polygon_t polygon,
                         std::vector<types::point_t> outlinePoints,
                         std::vector<types::segment_t> segments)
    : GraphEntity(Layers::TILES_LAYER,
                  types::point_t(bg::get<bg::min_corner, 0>(envelope),
                                 bg::get<bg::min_corner, 1>(envelope))),
      envelope(envelope), center(center), polygon(polygon),
      outlinePoints(outlinePoints), outlineSegments(segments),
      tilePtr(new Tile()) {}

VoronoiCell::~VoronoiCell() {}

types::coordinate_t VoronoiCell::getWidth() const {
  return bg::get<bg::max_corner, 0>(this->envelope) -
         bg::get<bg::min_corner, 0>(this->envelope);
}

types::coordinate_t VoronoiCell::getHeight() const {
  return bg::get<bg::max_corner, 1>(this->envelope) -
         bg::get<bg::min_corner, 1>(this->envelope);
}

bool VoronoiCell::isTargetable() const { return true; }

bool VoronoiCell::isSelectable() const { return false; }

const types::box_t &VoronoiCell::getEnvelope() const { return this->envelope; }

const types::point_t &VoronoiCell::getCenter() const { return this->center; }

const types::polygon_t &VoronoiCell::getPolygon() const {
  return this->polygon;
}

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
