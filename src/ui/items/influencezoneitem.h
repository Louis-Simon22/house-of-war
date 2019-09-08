#ifndef INFLUENCEZONEITEM_H
#define INFLUENCEZONEITEM_H

#include <QObject>
#include <QQuickItem>

#include "../../model/entities/zones/circularzone.h"
#include "../painters/basicshapepainter.h"
#include "./entityitem.h"

namespace how {
namespace ui {
class InfluenceZoneItem : public EntityItem {
  Q_OBJECT

  constexpr static float CIRCLE_LINE_WIDTH = 3;

public:
  InfluenceZoneItem(model::CircularZone *influenceZone, QQuickItem *parent);

private slots:
  void onGraphEntityUpdated();

private:
  const model::CircularZone *influenceZone;
  BasicShapePainter *circlePainter;
};
} // namespace ui
} // namespace how

#endif // INFLUENCEZONEITEM_H
