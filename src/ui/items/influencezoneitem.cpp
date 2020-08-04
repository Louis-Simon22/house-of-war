#include "influencezoneitem.h"

#include "../painters/painterutils.h"

namespace how {
namespace ui {

InfluenceZoneItem::InfluenceZoneItem(model::CircularZone *influenceZone,
                                     QQuickItem *parent)
    : EntityItem(influenceZone, parent), influenceZone(influenceZone),
      circlePainter(
          new BasicShapePainter(this, QSGGeometry::DrawLineLoop, Qt::red)) {
  circlePainter->setLineWidth(CIRCLE_LINE_WIDTH);
  this->onGraphEntityUpdated();
}

void InfluenceZoneItem::onGraphEntityUpdated() {
//  this->circlePainter->setPoints(
//      utils::getCirclePoints(0, 0, this->influenceZone->getRadius()));
  this->circlePainter->update();
}

} // namespace ui
} // namespace how
