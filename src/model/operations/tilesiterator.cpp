#include "tilesiterator.h"

namespace how {
namespace model {

void iterateTiles(GraphEntityManager *graphEntityManager) {
  auto &voronoiCellPtrs = graphEntityManager->getVoronoiCellPtrs();
  for (auto &voronoiCellPtr : voronoiCellPtrs) {
    auto &tile = voronoiCellPtr->getTile();
    tile.setResources(tile.getResources() + 1);
  }
}

} // namespace model
} // namespace how
