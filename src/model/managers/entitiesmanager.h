#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <memory>
#include <vector>

#include "../entities/army.h"
#include "../entities/character.h"
#include "./delaunayvoronoigraph.h"

namespace how {
namespace model {
class EntitiesManager {
public:
  EntitiesManager();

public:
  void generateEntities(const types::graph_t& graph);
  void addArmy(std::shared_ptr<Army> armyPtr);
  void addCharacter(std::shared_ptr<Character> characterPtr);

public:
  std::vector<std::shared_ptr<Army>> &getArmyPtrs();
  std::vector<std::shared_ptr<Character>> &getCharacterPtrs();
  std::vector<std::shared_ptr<VoronoiCell>> &getVoronoiCellPtrs();

private:
  std::vector<std::shared_ptr<Army>> armyPtrs;
  std::vector<std::shared_ptr<Character>> characterPtrs;
  std::vector<std::shared_ptr<VoronoiCell>> voronoiCellPtrs;
};
} // namespace model
} // namespace how

#endif // ENTITIESMANAGER_H
