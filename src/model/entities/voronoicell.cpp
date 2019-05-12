#include "voronoicell.h"

namespace how {
namespace model {

VoronoiCell::VoronoiCell() : GraphEntity() {}

VoronoiCell::VoronoiCell(types::box_t envelope,
                         std::vector<types::point_t> outlinePoints,
                         std::vector<types::segment_t> segments)
    : GraphEntity(VORONOI_CELL_LAYER), envelope(envelope),
      outlinePoints(outlinePoints), outlineSegments(segments), tile() {}

VoronoiCell::~VoronoiCell() {}

const types::box_t &VoronoiCell::getEnvelope() const { return this->envelope; }

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
