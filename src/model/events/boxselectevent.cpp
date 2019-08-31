#include "boxselectevent.h"

#include <boost/geometry/algorithms/convert.hpp>

#include "../operations/collisiondetector.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

BoxSelectEvent::BoxSelectEvent(const types::box_t &box, bool addToSelection)
    : box(box), addToSelection(addToSelection) {}

BoxSelectEvent::~BoxSelectEvent() {}

void BoxSelectEvent::applyEvent(EntitiesManager &entitiesManager,
                                SelectionManager &selectionManager) const {
  if (!this->addToSelection) {
    selectionManager.clearSelection();
  }
  const auto &box = this->box;
  const auto &armyPtrs = entitiesManager.getPlayers()[0].getArmyPtrs();
  auto selectedArmyPtrs =
      getCollisions<>(armyPtrs, [&box](const std::shared_ptr<Army> &armyPtr) {
        return armyPtr->getSelectionZone()->isBoxOverlappingZone(box);
      });
  for (auto &selectedArmyPtr : selectedArmyPtrs) {
    selectionManager.addArmySelection(selectedArmyPtr.get());
  }
}

} // namespace model
} // namespace how
