#ifndef VORONOICELL_H
#define VORONOICELL_H

#include "../entities/entity.h"
#include "../modeltypes.h"

namespace how {
namespace model {

struct VoronoiCell : public Entity {
public:
  VoronoiCell();
  VoronoiCell(types::point_t centroid, types::box_t envelope,
              types::polygon_t polygon,
              std::vector<types::point_t> outlinePoints,
              std::vector<types::segment_t> outlineSegments);

public:
  types::point_t centroid;
  types::box_t envelope;
  types::polygon_t polygon;
  std::vector<types::point_t> outlinePoints;
  std::vector<types::segment_t> outlineSegments;
};

} // namespace model
} // namespace how
#endif // VORONOICELL_H
