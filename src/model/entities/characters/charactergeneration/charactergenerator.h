#ifndef CHARACTERGENERATOR_H
#define CHARACTERGENERATOR_H

#include "../../../world/worlddata.h"
#include "../../../graphtypes.h"
#include "../characterdata.h"

#include <vector>

namespace how {
namespace model {
CharacterData *generateCharacters(const types::graph_t *delaunayGraphPtr);
} // namespace model
} // namespace how

#endif // CHARACTERGENERATOR_H
