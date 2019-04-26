#include "voronoicell.h"

namespace how {
namespace model {
VoronoiCell::VoronoiCell() : Entity() {}

VoronoiCell::VoronoiCell(types::box_t envelope, types::point_t centroid,
                         types::polygon_t polygon,
                         std::vector<types::point_t> outlinePoints,
                         std::vector<types::segment_t> segments)
    : Entity(), envelope(envelope), centroid(centroid), polygon(polygon),
      outlinePoints(outlinePoints), outlineSegments(segments), tile() {}

VoronoiCell::~VoronoiCell() {}

const types::box_t &VoronoiCell::getEnvelope() const { return this->envelope; }

const types::point_t &VoronoiCell::getCentroid() const {
  return this->centroid;
}

const types::polygon_t &VoronoiCell::getPolygon() const {
  return this->polygon;
}

const std::vector<types::point_t> &VoronoiCell::getOutlinePoints() const {
  return this->outlinePoints;
}

const std::vector<types::segment_t> &VoronoiCell::getOutlineSegments() const {
  return this->outlineSegments;
}

const Tile &VoronoiCell::getTile() const { return this->tile; }

Tile &VoronoiCell::getTile() { return this->tile; }

} // namespace model
} // namespace how
