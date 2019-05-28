#ifndef ARMYPAINTER_H
#define ARMYPAINTER_H

#include "../../model/entities/army.h"
#include "./painteritem.h"

namespace how {
namespace ui {
class ArmyPainter : public PainterItem {
public:
  ArmyPainter(QQuickItem *parent, std::shared_ptr<model::Army> armyPtr);
  ~ArmyPainter() override;

public:
  void updateDimensions() override;
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  std::shared_ptr<model::Army> armyPtr;
};
} // namespace ui
} // namespace how

#endif // ARMYPAINTER_H
