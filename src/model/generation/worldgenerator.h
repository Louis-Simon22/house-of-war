#ifndef WORLDBUILDER_H
#define WORLDBUILDER_H

#include "../graphtypes.h"
#include "../managers/worldmanager.h"
#include "./jcv_voronoi_adapter.h"
#include "./worldgenerationconfig.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

WorldManager *generateWorld(const WorldGenerationConfig &config);

} // namespace model
} // namespace how
#endif
