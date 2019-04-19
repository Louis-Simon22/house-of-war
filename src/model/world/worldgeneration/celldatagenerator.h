#ifndef CELLDATAGENERATOR_H
#define CELLDATAGENERATOR_H

#include "../../graphtypes.h"

namespace how {
namespace model {

void generateHeightData(types::box_t boundingBox, std::uint32_t randomSeed,
                      types::graph_t &graph);

} // namespace model
} // namespace how

#endif // CELLDATAGENERATOR_H
