#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <memory>
#include <vector>

#include "../entities/army.h"
#include "../entities/character.h"
#include "../utils/influencezonertree.h"

namespace how {
namespace model {
namespace {} // namespace
class EntitiesManager {
public:
  EntitiesManager();

public:
  void generateEntities(const types::graph_t &graph);

private:
  void addArmy(std::shared_ptr<Army> armyPtr);
  void addCharacter(std::shared_ptr<Character> characterPtr);

public:
  std::vector<std::shared_ptr<Army>> &getArmyPtrs();
  std::vector<std::shared_ptr<Character>> &getCharacterPtrs();
  std::vector<std::shared_ptr<VoronoiCell>> &getVoronoiCellPtrs();

private:
  std::vector<std::shared_ptr<Army>> armyPtrs;
  InfluenceZoneRTree<std::shared_ptr<Army>> armiesRtree;
  std::vector<std::shared_ptr<Character>> characterPtrs;
  InfluenceZoneRTree<std::shared_ptr<Character>> charactersRtree;
  std::vector<std::shared_ptr<VoronoiCell>> voronoiCellPtrs;
  InfluenceZoneRTree<std::shared_ptr<VoronoiCell>> voronoiCellsRtree;
};
} // namespace model
} // namespace how

#endif // ENTITIESMANAGER_H
