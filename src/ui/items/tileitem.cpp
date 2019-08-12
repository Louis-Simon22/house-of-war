#include "tileitem.h"

#include "../conversion/converter.h"

#include <iostream>

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

TileItem::~TileItem() {}

void TileItem::onTileDisplayStatusChanged() { this->onGraphEntityUpdated(); }

void TileItem::onGraphEntityUpdated() {
  QColor cellColor = Qt::black;
  switch (this->tilesController->getTileDisplayStatus()) {
  case TileDisplayStatusWrapper::TERRAIN: {
    auto terrainType = this->tile->getTerrainType();
    switch (terrainType) {
    case model::TerrainType::FOREST:
      cellColor = Qt::darkGreen;
      break;
    case model::TerrainType::MOUNTAIN:
      cellColor = Qt::gray;
      break;
    case model::TerrainType::PLAIN:
      cellColor = Qt::green;
      break;
    }
    break;
  }
  case TileDisplayStatusWrapper::OWNER: {
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
