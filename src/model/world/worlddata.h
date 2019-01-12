#ifndef WORLDDATA_H
#define WORLDDATA_H

#include <memory>
#include <vector>

#include "../modeltypes.h"

namespace how {
namespace model {

class WorldData {
public:
  WorldData(types::box_t bounds, std::vector<types::point_t> points, types::vd_t& vd);

  const std::vector<types::point_t> *getPointsList() const;

  const types::box_t &getBounds() const;

  const types::vd_t *getVoronoiDiagram() const;

private:
  types::box_t bounds;
  std::vector<types::point_t> points;
  types::vd_t& vd;
};
} // namespace model
} // namespace how
#endif // WORLDDATA_H
