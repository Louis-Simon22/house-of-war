#include "voronoicellitem.h"

#include "../conversion/converter.h"

namespace how {
namespace ui {
namespace {
namespace bg = ::boost::geometry;
}

VoronoiCellItem::VoronoiCellItem(
    std::shared_ptr<model::VoronoiCell> voronoiCellPtr, QQuickItem *parent)
    : GraphEntityItem(voronoiCellPtr, parent), voronoiCellPtr(voronoiCellPtr),
      voronoiCellPainter(new PolygonPainter(this)) {
  this->onGraphEntityUpdated();
}

void VoronoiCellItem::onGraphEntityUpdated() {
  const auto &envelope = voronoiCellPtr->getEnvelope();
  this->setX(static_cast<double>(bg::get<bg::min_corner, 0>(envelope)));
  this->setY(static_cast<double>(bg::get<bg::min_corner, 1>(envelope)));
  this->setZ(static_cast<double>(this->voronoiCellPtr->getLayer()));
  this->setWidth(static_cast<double>(bg::get<bg::max_corner, 0>(envelope) -
                                     bg::get<bg::min_corner, 0>(envelope)));
  this->setHeight(static_cast<double>(bg::get<bg::max_corner, 1>(envelope) -
                                      bg::get<bg::min_corner, 1>(envelope)));
  auto mappedPoints = std::vector<float>();
  for (const auto &point : this->voronoiCellPtr->getOutlinePoints()) {
    const auto mappedPoint =
        this->mapFromItem(this->parentItem(), convertF(point));
    mappedPoints.push_back(static_cast<float>(mappedPoint.x()));
    mappedPoints.push_back(static_cast<float>(mappedPoint.y()));
  }
  this->voronoiCellPainter->setPoints(mappedPoints);

  const auto altitude = this->voronoiCellPtr->getTile().getAltitude();
  const QColor color = QColor(0, static_cast<int>(altitude * 255),
                              static_cast<int>((1 - altitude) * 255));
  this->voronoiCellPainter->setColor(color);
}

} // namespace ui
} // namespace how
