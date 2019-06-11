#ifndef WORLDBUILDER_H
#define WORLDBUILDER_H

#include "../graphtypes.h"
#include "./worldgenerationconfig.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

std::pair<types::graph_t, types::graph_vertex_rtree_t>
generateGraph(const WorldGenerationConfig &config);

} // namespace model
} // namespace how
#endif
