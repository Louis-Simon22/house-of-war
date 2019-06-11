#include "armyitem.h"

namespace how {
namespace ui {

ArmyItem::ArmyItem(std::shared_ptr<model::Army> armyPtr, QQuickItem *parent)
    : EntityItem(armyPtr, parent), armyPtr(armyPtr),
      rectanglePainter(new RectanglePainter(Qt::red, 2, 3, this)),
      engagementZoneItem(
          new InfluenceZoneItem(armyPtr->getEngagementZonePtr(), this)),
      foragingZoneItem(
          new InfluenceZoneItem(armyPtr->getForagingZonePtr(), this)),
      scoutingZoneItem(
          new InfluenceZoneItem(armyPtr->getScoutingZonePtr(), this)) {
  this->onGraphEntityUpdated();
}

void ArmyItem::onGraphEntityUpdated() {
  this->setX(this->armyPtr->getPosX());
  this->setY(this->armyPtr->getPosY());
  this->setZ(static_cast<double>(this->armyPtr->getLayer()));
  this->rectanglePainter->setColor(this->armyPtr->isSelected() ? Qt::yellow
                                                               : Qt::red);
}

} // namespace ui
} // namespace how
