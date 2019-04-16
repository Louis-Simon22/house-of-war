#ifndef HEIGHTGENERATOR_H
#define HEIGHTGENERATOR_H

#include "../../delaunaygraphtypes.h"

namespace how {
namespace model {

std::vector<std::vector<types::coordinate_t>>
generateHeightMap(std::uint32_t randomSeed, types::delaunay_graph_t &graph);

} // namespace model
} // namespace how

#endif // HEIGHTGENERATOR_H
