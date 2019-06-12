#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <memory>
#include <vector>

#include "../entities/army.h"
#include "../entities/character.h"
#include "../utils/influencezonertree.h"

namespace how {
namespace model {
class EntitiesManager {
public:
  EntitiesManager();

public:
  void generateEntities(const types::graph_t &graph);
  types::graph_vertex_desc_t
  getVertexDescByPosition(const types::point_t &position);

private:
  void addArmy(std::shared_ptr<Army> armyPtr);
  void addCharacter(std::shared_ptr<Character> characterPtr);
  void addVoronoiCell(std::shared_ptr<VoronoiCell> voronoiCellPtr);

public:
  std::vector<std::shared_ptr<Army>> &getArmyPtrs();
  InfluenceZoneRTree<std::shared_ptr<Army>> &getArmiesRtree();
  std::vector<std::shared_ptr<Character>> &getCharacterPtrs();
  InfluenceZoneRTree<std::shared_ptr<Character>> &getCharactersRtree();
  std::vector<std::shared_ptr<VoronoiCell>> &getVoronoiCellPtrs();
  InfluenceZoneRTree<std::shared_ptr<VoronoiCell>> &getVoronoiCellsRtree();

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
