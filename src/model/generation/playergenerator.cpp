#include "playergenerator.h"

namespace how {
namespace model {

Player generatePlayer(const types::graph_t &graph) {
  auto player = Player();
  player.addArmy(new Army(graph[9]->getPosition()));
  player.addArmy(new Army(graph[30]->getPosition()));
  return player;
}

} // namespace model
} // namespace how
