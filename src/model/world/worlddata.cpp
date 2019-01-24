#include "worlddata.h"

namespace how {
namespace model {

WorldData::WorldData(types::box_t bounds, std::vector<types::point_t> points,
                     std::vector<types::segment_t> outlineSegments,
                     std::vector<VoronoiCell> voronoiCells)
    : bounds(bounds), points(points), outlineSegments(outlineSegments),
      voronoiCells(voronoiCells) {}

const std::vector<types::point_t> *WorldData::getPointsList() const {
  return &this->points;
}

const types::box_t &WorldData::getBounds() const { return this->bounds; }

const std::vector<types::segment_t> *WorldData::getOutlineSegments() const {
  return &this->outlineSegments;
}

const std::vector<VoronoiCell> *WorldData::getVoronoiCells() const {
  return &this->voronoiCells;
}

} // namespace model
} // namespace how
