#include "modeliterators.h"

#include "./collisiondetector.h"

namespace how {
namespace model {

void iterateMovement(EntitiesManager &entitiesManager) {
  auto &armyPtrs = entitiesManager.getPlayers()[0].getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    armyPtr->progressEntityPositionChange();
  }
}

void iterateTiles(EntitiesManager &entitiesManager) {
  auto &tilePtrs = entitiesManager.getTilePtrs();
  for (auto &tilePtr : tilePtrs) {
    tilePtr->setResources(tilePtr->getResources() + 3);
  }
}

void iterateArmies(EntitiesManager &entitiesManager) {
  auto &armyPtrs = entitiesManager.getPlayers()[0].getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    auto intersectingTiles =
        entitiesManager.getTilesRTree().getValuesByBoxIntersection(
            armyPtr->getForagingZone()->getEnvelope());
    for (auto intersectingTile : intersectingTiles) {
      if (armyPtr->getForagingZone()->isPolygonOverlappingZone(
              intersectingTile->getPolygon())) {
        intersectingTile->setResources(intersectingTile->getResources() - 3);
      }
    }
  }
}

} // namespace model
} // namespace how
