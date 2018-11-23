#ifndef WORLDBUILDER_H
#define WORLDBUILDER_H

#include "../../modeltypes.h"
#include "../worlddata.h"

namespace how {
namespace model {
class WorldBuilder {
 public:
  WorldBuilder(types::WorldGenerationConfig config);

  WorldData* build() const;

 private:
  types::point_t min_corner;
  types::point_t max_corner;
};
}  // namespace model
}  // namespace how
#endif
