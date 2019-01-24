#ifndef WORLDDATA_H
#define WORLDDATA_H

#include <memory>
#include <vector>

#include "../modeltypes.h"
#include "./voronoicell.h"

namespace how {
namespace model {

class WorldData {
public:
  WorldData(types::box_t bounds, std::vector<types::point_t> points,
            std::vector<types::segment_t> outlineSegments,
            std::vector<VoronoiCell> voronoiCells);

  const std::vector<types::point_t> *getPointsList() const;
  const types::box_t &getBounds() const;
  const std::vector<types::segment_t> *getOutlineSegments() const;
  const std::vector<VoronoiCell> *getVoronoiCells() const;

private:
  types::box_t bounds;
  std::vector<types::point_t> points;
  std::vector<types::segment_t> outlineSegments;
  std::vector<VoronoiCell> voronoiCells;
};
} // namespace model
} // namespace how
#endif // WORLDDATA_H
