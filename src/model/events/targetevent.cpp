#include "targetevent.h"

#include "../operations/pathfindingoperations.h"

namespace how {
namespace model {

TargetEvent::TargetEvent(types::coordinate_t posX, types::coordinate_t posY)
    : SpatialEvent(posX, posY) {}

TargetEvent::~TargetEvent() {}

void TargetEvent::applyEvent(EntitiesManager &entitiesManager,
                             SelectionManager &selectionManager) const {
  if (selectionManager.hasSelection()) {
    auto *sourceEntity = selectionManager.getSelection();
    const auto &sourceVertexDesc = entitiesManager.getVertexDescByPosition(
        sourceEntity->getAbsolutePosition());
    const auto &destinationVertexDesc =
        entitiesManager.getVertexDescByPosition(this->getPosition());
    auto destinations = graphEntityPathfinding(
        sourceVertexDesc, destinationVertexDesc, entitiesManager.getGraph());
    sourceEntity->setEntityPositionChange(
        new EntityPositionChange(sourceEntity, destinations));
  }
}

} // namespace model
} // namespace how
