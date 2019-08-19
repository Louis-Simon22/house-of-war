#include "targetevent.h"

#include "../operations/pathfindingoperations.h"

namespace how {
namespace model {

TargetEvent::TargetEvent(const types::point_t &position) : position(position) {}

TargetEvent::~TargetEvent() {}

void TargetEvent::applyEvent(EntitiesManager &entitiesManager,
                             SelectionManager &selectionManager) const {
  if (selectionManager.hasSelection()) {
    auto &tilesRTree = entitiesManager.getTilesRTree();
    auto *sourceEntity = selectionManager.getSelection();
    const auto &sourceTile =
        tilesRTree.getValueByPosition(sourceEntity->getAbsolutePosition());
    const auto &destinationTile = tilesRTree.getValueByPosition(this->position);
    auto destinations = graphEntityPathfinding(sourceTile->getVertexDesc(),
                                               destinationTile->getVertexDesc(),
                                               entitiesManager.getGraph());
    sourceEntity->setEntityPositionChange(
        new EntityPositionChange(sourceEntity, destinations));
  }
}

} // namespace model
} // namespace how
