#include "influencezoneitem.h"

namespace how {
namespace ui {

InfluenceZoneItem::InfluenceZoneItem(
    std::shared_ptr<model::CircularInfluenceZone> influenceZonePtr,
    QQuickItem *parent)
    : EntityItem(influenceZonePtr, parent), influenceZonePtr(influenceZonePtr),
      circlePainter(new CirclePainter(this, CIRCLE_LINE_WIDTH, CIRCLE_COLOR)) {
  this->onGraphEntityUpdated();
}

void InfluenceZoneItem::onGraphEntityUpdated() {
  this->circlePainter->setRadius(this->influenceZonePtr->getRadius());
  this->circlePainter->update();
}

} // namespace ui
} // namespace how
