#ifndef CHARACTERGENERATOR_H
#define CHARACTERGENERATOR_H

#include <vector>

#include "../entities/players/player.h"
#include "../graphtypes.h"

namespace how {
namespace model {

Player generatePlayer(const types::graph_t &graph);

} // namespace model
} // namespace how

#endif // CHARACTERGENERATOR_H
