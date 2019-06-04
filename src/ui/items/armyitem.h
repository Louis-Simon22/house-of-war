#ifndef ARMYITEM_H
#define ARMYITEM_H

#include <QQuickItem>

#include "../../model/entities/army.h"
#include "../painters/rectanglepainter.h"
#include "./influencezoneitem.h"
#include "./interactiveentityitem.h"

namespace how {
namespace ui {
class ArmyItem : public InteractiveEntityItem {
private:
  const QColor armyColor = Qt::red;
  const QColor engagementZoneColor = QColor(255, 0, 0, 0);
  const QColor foragingZoneColor = QColor(255, 0, 0, 0);
  const QColor scoutingZoneColor = QColor(255, 0, 0, 0);

public:
  ArmyItem(std::shared_ptr<model::Army> armyPtr, QQuickItem *parent);

protected:
  void onGraphEntityUpdated() override;

private:
  std::shared_ptr<const model::Army> armyPtr;
  RectanglePainter *rectanglePainter;
  InfluenceZoneItem *engagementZoneItem;
  InfluenceZoneItem *foragingZoneItem;
  InfluenceZoneItem *scoutingZoneItem;
};
} // namespace ui
} // namespace how

#endif // ARMYITEM_H
