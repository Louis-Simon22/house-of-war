#include "selectevent.h"

namespace how {
namespace model {

SelectEvent::SelectEvent(types::coordinate_t posX, types::coordinate_t posY)
    : SpatialEvent(posX, posY) {}

SelectEvent::~SelectEvent() {}

void SelectEvent::applyEvent(EntitiesManager &,
                             SelectionManager &selectionManager) const {
  selectionManager.selectByPosition(this->getPosition());
}

} // namespace model
} // namespace how
