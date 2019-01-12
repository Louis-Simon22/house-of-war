#ifndef WORLDBUILDER_H
#define WORLDBUILDER_H

#include "../../modeltypes.h"
#include "../worlddata.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}
class WorldBuilder {
public:
  WorldBuilder(const types::WorldGenerationConfig &config);

  WorldData *build() const;

private:
  types::point_t min_corner;
  types::point_t max_corner;
};
} // namespace model
} // namespace how
#endif
