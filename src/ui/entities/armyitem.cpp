#include "armyitem.h"

namespace how {
namespace ui {

ArmyItem::ArmyItem(std::shared_ptr<model::Army> armyPtr, QQuickItem *parent)
    : GraphEntityItem(armyPtr, parent), armyPtr(armyPtr),
      armyPainter(new RectanglePainter(this, armyColor)),
      engagementZonePainter(
          new CirclePainter(this, ZONE_LINE_WIDTH, engagementZoneColor)),
      foragingZonePainter(
          new CirclePainter(this, ZONE_LINE_WIDTH, foragingZoneColor)),
      scoutingZonePainter(
          new CirclePainter(this, ZONE_LINE_WIDTH, scoutingZoneColor)) {
  this->onGraphEntityUpdated();
}

void ArmyItem::onGraphEntityUpdated() {
  // TODO fix this mess by having child items for zones which will draw
  // according to their parent's position and have their own events
  const auto armyPosX = static_cast<double>(this->armyPtr->getPosX());
  const auto armyPosY = static_cast<double>(this->armyPtr->getPosY());
  const auto engagementZoneRadius =
      static_cast<double>(this->armyPtr->getEngagementZone().getRadius());
  const auto foragingZoneRadius =
      static_cast<double>(this->armyPtr->getForagingZone().getRadius());
  const auto scoutingZoneRadius =
      static_cast<double>(this->armyPtr->getScoutingZone().getRadius());
  const auto biggestRadius =
      std::max({engagementZoneRadius, foragingZoneRadius, scoutingZoneRadius});
  this->setX(armyPosX - biggestRadius);
  this->setY(armyPosY - biggestRadius);
  this->setZ(static_cast<double>(this->armyPtr->getLayer()));
  this->setWidth(biggestRadius);
  this->setHeight(biggestRadius);
  this->armyPainter->setX(armyPosX);
  this->armyPainter->setY(armyPosX);
  this->armyPainter->setWidth(3);
  this->armyPainter->setHeight(3);
  this->engagementZonePainter->setX(biggestRadius - engagementZoneRadius);
  this->engagementZonePainter->setY(biggestRadius - engagementZoneRadius);
  this->engagementZonePainter->setWidth(engagementZoneRadius * 2);
  this->engagementZonePainter->setHeight(engagementZoneRadius * 2);
  this->foragingZonePainter->setX(biggestRadius - foragingZoneRadius);
  this->foragingZonePainter->setY(biggestRadius - foragingZoneRadius);
  this->foragingZonePainter->setWidth(foragingZoneRadius * 2);
  this->foragingZonePainter->setHeight(foragingZoneRadius * 2);
  this->scoutingZonePainter->setX(biggestRadius - scoutingZoneRadius);
  this->scoutingZonePainter->setY(biggestRadius - scoutingZoneRadius);
  this->scoutingZonePainter->setWidth(scoutingZoneRadius * 2);
  this->scoutingZonePainter->setHeight(scoutingZoneRadius * 2);
}

} // namespace ui
} // namespace how
