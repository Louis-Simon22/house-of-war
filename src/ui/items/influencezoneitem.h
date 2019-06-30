#ifndef INFLUENCEZONEITEM_H
#define INFLUENCEZONEITEM_H

#include <QObject>
#include <QQuickItem>

#include "../../model/entities/circularinfluencezone.h"
#include "../painters/circlepainter.h"
#include "./entityitem.h"

namespace how {
namespace ui {
class InfluenceZoneItem : public EntityItem {
  Q_OBJECT

  constexpr static float CIRCLE_LINE_WIDTH = 3;
  const QColor CIRCLE_COLOR = Qt::red;

public:
  InfluenceZoneItem(
      model::CircularInfluenceZone* influenceZone,
      QQuickItem *parent);

private slots:
  void onGraphEntityUpdated();

private:
  const model::CircularInfluenceZone* influenceZone;
  CirclePainter *circlePainter;
};
} // namespace ui
} // namespace how

#endif // INFLUENCEZONEITEM_H
