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
      std::shared_ptr<model::CircularInfluenceZone> influenceZonePtr,
      QQuickItem *parent);

private slots:
  void onGraphEntityUpdated();

private:
  std::shared_ptr<const model::CircularInfluenceZone> influenceZonePtr;
  CirclePainter *circlePainter;
};
} // namespace ui
} // namespace how

#endif // INFLUENCEZONEITEM_H
