#ifndef ARMYITEM_H
#define ARMYITEM_H

#include <QQuickItem>

#include "../../model/entities/characters/army.h"
#include "../painters/pathpainter.h"
#include "../painters/rectanglepainter.h"
#include "./entityitem.h"
#include "./influencezoneitem.h"

namespace how {
namespace ui {
class ArmyItem : public EntityItem {
  Q_OBJECT

private:
  const QColor armyColor = Qt::red;
  const QColor engagementZoneColor = QColor(255, 0, 0, 0);
  const QColor foragingZoneColor = QColor(255, 0, 0, 0);
  const QColor scoutingZoneColor = QColor(255, 0, 0, 0);

public:
  ArmyItem(model::Army *army, QQuickItem *parent);

protected:
  void onGraphEntityUpdated() override;

private:
  const model::Army *army;
  RectanglePainter *rectanglePainter;
  PathPainter *pathPainter;
  InfluenceZoneItem *engagementZoneItem;
  InfluenceZoneItem *foragingZoneItem;
  InfluenceZoneItem *scoutingZoneItem;
};
} // namespace ui
} // namespace how

#endif // ARMYITEM_H
