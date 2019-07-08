#include "tileitem.h"

#include "../conversion/converter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

TileItem::TileItem(model::Tile *tile, const TilesController *tilesController,
                   QQuickItem *parent)
    : EntityItem(tile, parent), tile(tile), tilesController(tilesController),
      voronoiCellPainter(
          new PolygonPainter(tile->getRelativeOutlinePoints(), this)),
      voronoiCellOutlinePainter(
          new PolygonOutlinePainter(this, tile->getRelativeOutlinePoints())) {
  this->setX(this->tile->getPosX());
  this->setY(this->tile->getPosY());
  this->setZ(this->tile->getLayer());
  this->voronoiCellOutlinePainter->setColor(QColor(255, 255, 0));
  this->onTileDisplayStatusChanged();
  this->onGraphEntityUpdated();
}

void TileItem::onTileDisplayStatusChanged() { this->onGraphEntityUpdated(); }

void TileItem::onGraphEntityUpdated() {
  QColor cellColor = Qt::black;
  switch (this->tilesController->getTileDisplayStatus()) {
  case TileDisplayStatusWrapper::TILE_DISPLAY_STATUS_TERRAIN: {
    const auto altitude = this->tile->getAltitude();
    cellColor = QColor(0, static_cast<int>(altitude * 255), 0);
    break;
  }
  case TileDisplayStatusWrapper::TILE_DISPLAY_STATUS_ALTITUDE: {
    const auto altitude = this->tile->getAltitude();
    cellColor = QColor(0, static_cast<int>(altitude * 255), 0);
    break;
  }
  case TileDisplayStatusWrapper::TILE_DISPLAY_STATUS_RESOURCES: {
    const auto resources = this->tile->getResources();
    cellColor = QColor(0, static_cast<int>(resources),
                       static_cast<int>(255 - resources));
    break;
  }
  case TileDisplayStatusWrapper::TILE_DISPLAY_STATUS_OWNER: {
    const auto *owner = this->tile->getOwner();
    cellColor = owner ? Qt::blue : Qt::black;
    break;
  }
  }

  this->voronoiCellPainter->setColor(cellColor);

  this->voronoiCellOutlinePainter->setVisible(this->tile->isSelected());
}

} // namespace ui
} // namespace how
