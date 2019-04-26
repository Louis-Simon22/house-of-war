#ifndef CHARACTERGENERATOR_H
#define CHARACTERGENERATOR_H

#include <vector>

#include "../graphtypes.h"
#include "../managers/worldmanager.h"
#include "../entities/character.h"

namespace how {
namespace model {

std::vector<Character> generateCharacters(const types::graph_t *delaunayGraphPtr);

} // namespace model
} // namespace how

#endif // CHARACTERGENERATOR_H
