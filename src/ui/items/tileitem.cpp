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
          new BasicShapePainter(this, QSGGeometry::DrawTriangleFan, Qt::red,
                                tile->getRelativeOutlinePoints())),
      selectionOutlinePainter(new BasicShapePainter(
          this, QSGGeometry::DrawLineLoop, Qt::yellow,
          tile->getRelativeOutlinePoints(), SELECTION_OUTLINE_WIDTH)),
      roadsPainter(
          new BasicShapePainter(this, QSGGeometry::DrawLines, Qt::black,
                                tile->getRoadSegmentsAsPoints(), ROADS_WIDTH)) {
  this->setX(this->tile->getPosX());
  this->setY(this->tile->getPosY());
  this->setZ(this->tile->getLayer());
  this->onTileDisplayStatusChanged();
}

TileItem::~TileItem() {}

void TileItem::onTileDisplayStatusChanged() { this->onGraphEntityUpdated(); }

void TileItem::onGraphEntityUpdated() {
  QColor cellColor = Qt::black;
  switch (this->tilesController->getTileDisplayStatus()) {
  case TileDisplayStatusWrapper::TERRAIN: {
    switch (this->tile->getTerrainType()) {
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

  this->selectionOutlinePainter->setVisible(this->tile->isSelected());
}

} // namespace ui
} // namespace how
