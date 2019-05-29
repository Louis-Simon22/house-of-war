#ifndef INFLUENCEZONEITEM_H
#define INFLUENCEZONEITEM_H

#include <QObject>
#include <QQuickItem>

#include "../../model/entities/influencezone.h"
#include "../painters/circlepainter.h"

namespace how {
namespace ui {
class InfluenceZoneItem : public QQuickItem {
  Q_OBJECT

  constexpr static float CIRCLE_LINE_WIDTH = 3;
  const QColor CIRCLE_COLOR = Qt::red;

public:
  InfluenceZoneItem(const model::InfluenceZone &influenceZone,
                    QObject *memoryParent, QQuickItem *visualParent);

private slots:
  void onGraphEntityUpdated();

private:
  const model::InfluenceZone &influenceZone;
  CirclePainter *circlePainter;
};
} // namespace ui
} // namespace how

#endif // INFLUENCEZONEITEM_H
