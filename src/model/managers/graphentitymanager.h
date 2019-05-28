#ifndef GRAPHENTITYMANAGER_H
#define GRAPHENTITYMANAGER_H

#include <list>
#include <memory>
#include <vector>

#include "../entities/army.h"
#include "../entities/character.h"
#include "../entities/graphentitychange.h"

namespace how {
namespace model {
class GraphEntityManager {
public:
  GraphEntityManager(types::graph_t graph, types::box_t bounds);

public:
  void addGraphEntityPositionChange(GraphEntity *source,
                                    GraphEntity *destination);
  void iterateAllEntityChanges();
  void addArmy(std::shared_ptr<Army> armyPtr);
  void addCharacter(std::shared_ptr<Character> characterPtr);
  void addVoronoiCell(std::shared_ptr<VoronoiCell> voronoiCellPtr);

public:
  const types::graph_t &getGraph() const;
  const types::box_t &getBounds() const;
  const types::spatial_index_tree_t &getSpatialIndexTree() const;
  const std::vector<types::segment_t> &getVoronoiSegments() const;
  const std::vector<types::segment_t> &getDelaunaySegments() const;
  std::vector<std::shared_ptr<Army>> &getArmyPtrs();
  std::vector<std::shared_ptr<Character>> &getCharacterPtrs();
  std::vector<std::shared_ptr<VoronoiCell>> &getVoronoiCellPtrs();
  std::shared_ptr<::how::model::VoronoiCell>
  getVoronoiCellPtrByDesc(types::graph_vertex_desc_t vertexDesc);
  types::graph_vertex_desc_t
  getVertexDescByPosition(types::point_t position) const;
  VoronoiCell *getVoronoiCellByPosition(types::point_t position) const;

private:
  std::vector<VoronoiCell *> getDestinationsBetween(GraphEntity *source,
                                                    GraphEntity *destination);

private:
  types::graph_t graph;
  types::box_t bounds;
  types::spatial_index_tree_t spatialIndexTree;
  std::vector<types::segment_t> voronoiSegments;
  std::vector<types::segment_t> delaunaySegments;
  std::list<std::unique_ptr<GraphEntityChange>> graphEntityChangePtrs;
  std::vector<std::shared_ptr<Army>> armyPtrs;
  std::vector<std::shared_ptr<Character>> characterPtrs;
  std::vector<std::shared_ptr<VoronoiCell>> voronoiCellPtrs;
};
} // namespace model
} // namespace how

#endif // GRAPHENTITYMANAGER_H
