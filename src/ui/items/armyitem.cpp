#include "armyitem.h"

#include "painterutils.h"

namespace how {
namespace ui {

ArmyItem::ArmyItem(model::Army *army, QQuickItem *parent)
    : EntityItem(army, parent), army(army),
      armyShapePainter(new BasicShapePainter(
          this, QSGGeometry::DrawTriangleFan, Qt::red,
          utils::getRectanglePointsClockwise(0, 0, 5, 5))),
      pathPainter(
          new BasicShapePainter(this, QSGGeometry::DrawLineStrip, Qt::yellow)),
      engagementZoneItem(
          new InfluenceZoneItem(army->getEngagementZone(), this)),
      foragingZoneItem(new InfluenceZoneItem(army->getForagingZone(), this)),
      scoutingZoneItem(new InfluenceZoneItem(army->getScoutingZone(), this)) {
  this->pathPainter->setLineWidth(5);
  this->onGraphEntityUpdated();
}

void ArmyItem::onGraphEntityUpdated() {
  this->setX(this->army->getPosX());
  this->setY(this->army->getPosY());
  this->setZ(static_cast<double>(this->army->getLayer()));
  this->armyShapePainter->setColor(this->army->isSelected() ? Qt::yellow
                                                            : Qt::red);
  auto entityPositionChange = this->army->getEntityPositionChange();
  if (entityPositionChange) {
    this->pathPainter->setPoints(
        entityPositionChange->getPathAsRelativePoints());
  } else {
    this->pathPainter->clearPoints();
  }
}

} // namespace ui
} // namespace how
