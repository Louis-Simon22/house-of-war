#include "tilescontroller.h"

#include <iostream>

namespace how {
namespace ui {

TilesController::TilesController()
    : QObject(nullptr),
      currentTileDisplayStatus(
          TileDisplayStatusWrapper::DEFAULT),
      currentTerrainType(model::TerrainType::DEFAULT) {}

TileDisplayStatusWrapper::TileDisplayStatus
TilesController::getTileDisplayStatus() const {
  return this->currentTileDisplayStatus;
}

model::TerrainType TilesController::getTerrainType() const {
  return static_cast<model::TerrainType>(this->currentTerrainType);
}

void TilesController::setTileDisplayStatus(int tileDisplayStatus) {
  this->currentTileDisplayStatus =
      static_cast<TileDisplayStatusWrapper::TileDisplayStatus>(
          tileDisplayStatus);
  this->onTileDisplayStatusChanged();
}

} // namespace ui
} // namespace how
