#ifndef WORLDBUILDER_H
#define WORLDBUILDER_H

#include "../graphtypes.h"
#include "./worldgenerationconfig.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

types::graph_t generateGraph(const WorldGenerationConfig &config);

types::graph_t generateGraph(const WorldGenerationConfig &config,
                             std::vector<std::shared_ptr<Tile>> tilePtrs);

} // namespace model
} // namespace how
#endif
