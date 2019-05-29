#include "influencezoneitem.h"

namespace how {
namespace ui {

InfluenceZoneItem::InfluenceZoneItem(const model::InfluenceZone &influenceZone,
                                     QObject *memoryParent,
                                     QQuickItem *visualParent)
    : influenceZone(influenceZone),
      circlePainter(new CirclePainter(this, CIRCLE_LINE_WIDTH, CIRCLE_COLOR)) {
  this->setParent(memoryParent);
    this->setParentItem(visualParent);
    this->onGraphEntityUpdated();
}

void InfluenceZoneItem::onGraphEntityUpdated()
{
    const auto envelope = this->influenceZone.getEnvelope();
//    this->circlePainter->setX()
}

} // namespace ui
} // namespace how
