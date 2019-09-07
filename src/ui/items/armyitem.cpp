#include "armyitem.h"

#include "painterutils.h"

namespace how {
namespace ui {

ArmyItem::ArmyItem(model::Army *army, QQuickItem *parent)
    : EntityItem(army, parent), army(army),
      basicShapePainter(
          new BasicShapePainter(QSGGeometry::DrawTriangleFan, Qt::red, this)),
      pathPainter(new PathPainter(getCornersOfRectangle(0, 0, 10, 10), this)),
      engagementZoneItem(
          new InfluenceZoneItem(army->getEngagementZone(), this)),
      foragingZoneItem(new InfluenceZoneItem(army->getForagingZone(), this)),
      scoutingZoneItem(new InfluenceZoneItem(army->getScoutingZone(), this)) {
  this->onGraphEntityUpdated();
}

void ArmyItem::onGraphEntityUpdated() {
  this->setX(this->army->getPosX());
  this->setY(this->army->getPosY());
  this->setZ(static_cast<double>(this->army->getLayer()));
  this->basicShapePainter->setColor(this->army->isSelected() ? Qt::yellow
                                                             : Qt::red);
  auto entityPositionChange = this->army->getEntityPositionChange();
  if (entityPositionChange) {
    this->pathPainter->setPoints(
        entityPositionChange->getRemainingDestinations());
  }
} // namespace ui

} // namespace ui
} // namespace how
