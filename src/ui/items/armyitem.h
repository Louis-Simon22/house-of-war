#ifndef ARMYITEM_H
#define ARMYITEM_H

#include <QQuickItem>

#include "../../model/entities/characters/army.h"
#include "../painters/basicshapepainter.h"
#include "./entityitem.h"
#include "./influencezoneitem.h"

namespace how {
namespace ui {
class ArmyItem : public EntityItem {
  Q_OBJECT

  constexpr static float PATH_LINE_WIDTH = 3;

public:
  ArmyItem(model::Army *army, QQuickItem *parent);

protected:
  void onGraphEntityUpdated() override;

private:
  const model::Army *army;
  BasicShapePainter *armyShapePainter;
  BasicShapePainter *pathPainter;
  InfluenceZoneItem *engagementZoneItem;
  InfluenceZoneItem *foragingZoneItem;
  InfluenceZoneItem *scoutingZoneItem;
};
} // namespace ui
} // namespace how

#endif // ARMYITEM_H
