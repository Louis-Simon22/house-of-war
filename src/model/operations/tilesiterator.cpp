#include "tilesiterator.h"

namespace how {
namespace model {

void iterateTiles(EntitiesManager &entitiesManager) {
  auto &voronoiCellPtrs = entitiesManager.getVoronoiCellPtrs();
  for (auto &voronoiCellPtr : voronoiCellPtrs) {
    auto &tile = voronoiCellPtr->getTile();
    tile.setResources(tile.getResources() + 1);
  }
}

} // namespace model
} // namespace how
