#include "tilescontroller.h"

#include <iostream>

namespace how {
namespace ui {

TilesController::TilesController()
    : QObject(nullptr),
      currentTileDisplayStatus(
          TileDisplayStatusWrapper::TILE_DISPLAY_STATUS_RESOURCES) {}

TileDisplayStatusWrapper::TileDisplayStatus
TilesController::getTileDisplayStatus() const {
  return this->currentTileDisplayStatus;
}

void TilesController::setTileDisplayStatus(int tileDisplayStatus) {
  std::cout << "Greg" << std::endl;
  this->currentTileDisplayStatus =
      static_cast<TileDisplayStatusWrapper::TileDisplayStatus>(
          tileDisplayStatus);
  this->onTileDisplayStatusChanged();
}

} // namespace ui
} // namespace how
