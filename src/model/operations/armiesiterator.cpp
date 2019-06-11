#include "armiesiterator.h"

#include "./polygonindexoperations.h"

namespace how {
namespace model {

void iterateArmies(EntitiesManager &entitiesManager,
                   GraphManager *delaunayVoronoiGraph) {
  auto &armyPtrs = entitiesManager.getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    auto intersectedVertexIds =
        intersectingArea(armyPtr->getForagingZonePtr()->getEnvelope(),
                         delaunayVoronoiGraph->getSpatialIndexTree());
    for (auto intersectedVertexId : intersectedVertexIds) {
      auto voronoiCellPtr =
          delaunayVoronoiGraph->getVoronoiCellPtrByDesc(intersectedVertexId);
      if (armyPtr->getScoutingZonePtr()->isPointWithinZone(
              voronoiCellPtr->getPosX(), voronoiCellPtr->getPosY())) {
        voronoiCellPtr->getTile().getResources() -= 3;
      }
    }
  }
}

} // namespace model
} // namespace how
