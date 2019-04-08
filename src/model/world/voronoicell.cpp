#include "voronoicell.h"

namespace how {
namespace model {
VoronoiCell::VoronoiCell() : Entity() {}

VoronoiCell::VoronoiCell(types::point_t centroid, types::box_t envelope,
                         types::polygon_t polygon,
                         std::vector<types::point_t> outlinePoints,
                         std::vector<types::segment_t> segments)
    : Entity(), centroid(centroid), envelope(envelope), polygon(polygon),
      outlinePoints(outlinePoints), outlineSegments(segments) {}

} // namespace model
} // namespace how
