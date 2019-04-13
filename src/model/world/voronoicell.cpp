#include "voronoicell.h"

namespace how {
namespace model {
VoronoiCell::VoronoiCell() : Entity() {}

VoronoiCell::VoronoiCell(types::box_t envelope, types::point_t centroid,
                         types::polygon_t polygon,
                         std::vector<types::point_t> outlinePoints,
                         std::vector<types::segment_t> segments)
    : Entity(), envelope(envelope), centroid(centroid), polygon(polygon),
      outlinePoints(outlinePoints), outlineSegments(segments), cellData() {}

} // namespace model
} // namespace how
