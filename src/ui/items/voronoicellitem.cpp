#include "voronoicellitem.h"

#include "../conversion/converter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

VoronoiCellItem::VoronoiCellItem(
    std::shared_ptr<model::VoronoiCell> voronoiCellPtr, QQuickItem *parent)
    : EntityItem(voronoiCellPtr, parent), voronoiCellPtr(voronoiCellPtr),
      voronoiCellPainter(new PolygonPainter(
          this, voronoiCellPtr->getRelativeOutlinePoints())) {
  this->setX(this->voronoiCellPtr->getPosX());
  this->setY(this->voronoiCellPtr->getPosY());
  this->setZ(this->voronoiCellPtr->getLayer());
  this->onGraphEntityUpdated();
}

void VoronoiCellItem::onGraphEntityUpdated() {
  const auto altitude = this->voronoiCellPtr->getTile().getAltitude();
  const QColor color = QColor(0, static_cast<int>(altitude * 255),
                              static_cast<int>((1 - altitude) * 255));
  this->voronoiCellPainter->setColor(color);
  this->voronoiCellPainter->update();
}

model::VoronoiCell *VoronoiCellItem::getVoronoiCell() {
  return this->voronoiCellPtr.get();
}

} // namespace ui
} // namespace how
