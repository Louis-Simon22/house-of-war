#ifndef ARMYITEM_H
#define ARMYITEM_H

#include <QQuickItem>

#include "../../model/entities/army.h"
#include "./graphentityitem.h"

namespace how {
namespace ui {
class ArmyItem : public GraphEntityItem {
public:
  ArmyItem(QQuickItem *parent, std::shared_ptr<model::Army> armyPtr);

public slots:
  void updateDimensions();

private:
  std::shared_ptr<model::Army> armyPtr;
};
} // namespace ui
} // namespace how

#endif // ARMYITEM_H
