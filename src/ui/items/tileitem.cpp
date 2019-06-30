#include "tileitem.h"

#include "../conversion/converter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

TileItem::TileItem(model::Tile *tile, QQuickItem *parent)
    : EntityItem(tile, parent), tile(tile),
      voronoiCellPainter(
          new PolygonPainter(tile->getRelativeOutlinePoints(), this)),
      voronoiCellOutlinePainter(
          new PolygonOutlinePainter(this, tile->getRelativeOutlinePoints())) {
  this->setX(this->tile->getPosX());
  this->setY(this->tile->getPosY());
  this->setZ(this->tile->getLayer());
  this->voronoiCellOutlinePainter->setColor(QColor(255, 255, 0));
  this->onGraphEntityUpdated();
}

void TileItem::onGraphEntityUpdated() {
  const auto resources = this->tile->getResources();
  const QColor color = QColor(0, static_cast<int>(resources),
                              static_cast<int>(255 - resources), 255);

  this->voronoiCellPainter->setColor(color);

  this->voronoiCellOutlinePainter->setVisible(this->tile->isSelected());
}

} // namespace ui
} // namespace how
