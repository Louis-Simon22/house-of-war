#ifndef ARMYITEM_H
#define ARMYITEM_H

#include <QQuickItem>

#include "../../model/entities/army.h"
#include "../painters/circlepainter.h"
#include "../painters/rectanglepainter.h"
#include "./graphentityitem.h"

namespace how {
namespace ui {
class ArmyItem : public GraphEntityItem {
private:
  const QColor armyColor = Qt::red;
  const QColor engagementZoneColor = QColor(255, 0, 0, 0);
  const QColor foragingZoneColor = QColor(255, 0, 0, 0);
  const QColor scoutingZoneColor = QColor(255, 0, 0, 0);
  static constexpr float ZONE_LINE_WIDTH = 2;

public:
  ArmyItem(std::shared_ptr<model::Army> armyPtr, QQuickItem *parent = nullptr);

protected:
  void onGraphEntityUpdated() override;

private:
  std::shared_ptr<model::Army> armyPtr;
  RectanglePainter *armyPainter;
  CirclePainter *engagementZonePainter;
  CirclePainter *foragingZonePainter;
  CirclePainter *scoutingZonePainter;
};
} // namespace ui
} // namespace how

#endif // ARMYITEM_H
