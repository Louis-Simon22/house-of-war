#include "voronoicell.h"

namespace how {
namespace model {
VoronoiCell::VoronoiCell(types::point_t centroid, types::polygon_t polygon,
                         std::vector<types::segment_t> segments)
    : centroid(centroid), polygon(polygon), segments(segments) {}
} // namespace model
} // namespace how
