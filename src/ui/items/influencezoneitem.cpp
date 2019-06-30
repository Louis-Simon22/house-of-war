#include "influencezoneitem.h"

namespace how {
namespace ui {

InfluenceZoneItem::InfluenceZoneItem(
    model::CircularInfluenceZone* influenceZone,
    QQuickItem *parent)
    : EntityItem(influenceZone, parent), influenceZone(influenceZone),
      circlePainter(new CirclePainter(this, CIRCLE_LINE_WIDTH, CIRCLE_COLOR)) {
  this->onGraphEntityUpdated();
}

void InfluenceZoneItem::onGraphEntityUpdated() {
  this->circlePainter->setRadius(this->influenceZone->getRadius());
  this->circlePainter->update();
}

} // namespace ui
} // namespace how
