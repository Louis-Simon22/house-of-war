#include "armyitem.h"

namespace how {
namespace ui {

ArmyItem::ArmyItem(model::Army *army, QQuickItem *parent)
    : EntityItem(army, parent), army(army),
      rectanglePainter(new RectanglePainter(2, 3, this)),
      pathPainter(new PathPainter(std::vector<types::point_t>(), this)),
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
  this->rectanglePainter->setColor(this->army->isSelected() ? Qt::yellow
                                                            : Qt::red);
  auto entityPositionChange = this->army->getEntityPositionChange();
  this->pathPainter->setPoints(entityPositionChange
                               ? entityPositionChange->getRemainingDestinations()
                               : std::vector<types::point_t>());
}

} // namespace ui
} // namespace how
