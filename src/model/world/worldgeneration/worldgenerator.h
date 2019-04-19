#ifndef WORLDBUILDER_H
#define WORLDBUILDER_H

#include "jcv_voronoi_adapter.h"

#include "../../modeltypes.h"
#include "../../graphtypes.h"
#include "../worlddata.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

WorldData* generateWorld(const types::WorldGenerationConfig &config);

} // namespace model
} // namespace how
#endif
