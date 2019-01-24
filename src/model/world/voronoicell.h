#ifndef VORONOICELL_H
#define VORONOICELL_H

#include "../modeltypes.h"

namespace how {
namespace model {

struct VoronoiCell {
public:
  VoronoiCell(types::point_t centroid, types::polygon_t polygon,
              std::vector<types::segment_t> segments);

public:
  types::point_t centroid;
  types::polygon_t polygon;
  std::vector<types::segment_t> segments;
};

} // namespace model
} // namespace how
#endif // VORONOICELL_H
