#ifndef WORLDDATA_H
#define WORLDDATA_H

#include <memory>
#include <vector>

#include "../modeltypes.h"

namespace how {
namespace model {
class WorldData {
 public:
  WorldData(types::box_t bounds, std::vector<types::point_t> points);

  const std::vector<types::point_t>* getPointsList() const;

  const types::box_t& getBounds() const;

 private:
  std::vector<types::point_t> points;
  types::box_t bounds;
};
}  // namespace model
}  // namespace how
#endif  // WORLDDATA_H
