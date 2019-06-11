#include "voronoicellbindings.h"

namespace how {
namespace ui {

VoronoiCellBindings::VoronoiCellBindings() : voronoiCellItem(nullptr) {}

void VoronoiCellBindings::onVoronoiCellItemSelected(
    how::ui::VoronoiCellItem *voronoiCellItem) {
  this->voronoiCellItem = voronoiCellItem;
  this->updateBindings();
}

bool VoronoiCellBindings::isBound() const { return this->voronoiCellItem; }

types::carac_t VoronoiCellBindings::getAltitude() const {
  return this->voronoiCellItem
             ? this->voronoiCellItem->getVoronoiCell()->getTile().getAltitude()
             : 0;
}

} // namespace ui
} // namespace how
