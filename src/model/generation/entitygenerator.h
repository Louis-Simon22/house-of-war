#ifndef CHARACTERGENERATOR_H
#define CHARACTERGENERATOR_H

#include <vector>

#include "../graphtypes.h"
#include "../entities/character.h"
#include "../entities/army.h"
#include "../managers/graphentitymanager.h"

namespace how {
namespace model {

std::vector<std::shared_ptr<Character>> generateCharacters(const types::graph_t &delaunayGraphPtr);

std::vector<std::shared_ptr<Army>> generateArmies(const types::graph_t &delaunayGraphPtr);

} // namespace model
} // namespace how

#endif // CHARACTERGENERATOR_H
