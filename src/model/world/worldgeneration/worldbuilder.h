#ifndef WORLDBUILDER_H
#define WORLDBUILDER_H

#include "jcv_voronoi_adapter.h"

#include "../../modeltypes.h"
#include "../worlddata.h"
#include "../../../utils/algo/poissondisksampling.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

WorldData* buildWorld(const types::WorldGenerationConfig &config);

types::delaunayGraph *extrapolateDelaunayTriangulation(std::vector<types::segment_t> edges);

} // namespace model
} // namespace how
#endif
