#include "armiesiterator.h"

#include "./polygonindexoperations.h"

namespace how {
namespace model {

void iterateArmies(GraphEntityManager *graphEntityManager) {
  auto &armyPtrs = graphEntityManager->getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    auto intersectedVertexIds =
        intersectingArea(armyPtr->getForagingZone().getEnvelope(),
                         graphEntityManager->getSpatialIndexTree());
    for (auto intersectedVertexId : intersectedVertexIds) {
      auto voronoiCellPtr =
          graphEntityManager->getVoronoiCellPtrByDesc(intersectedVertexId);
      if (armyPtr->getScoutingZone().isPointWithinZone(
              voronoiCellPtr->getPosX(), voronoiCellPtr->getPosY())) {
        voronoiCellPtr->getTile().getResources() -= 3;
      }
    }
  }
}

} // namespace model
} // namespace how
