#ifndef ARMYPAINTER_H
#define ARMYPAINTER_H

#include "../../model/entities/army.h"
#include "./entitypainter.h"

namespace how {
namespace ui {
class ArmyPainter : public EntityPainter {
public:
  ArmyPainter(model::Army &army);
  ~ArmyPainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  model::Army &army;
};
} // namespace ui
} // namespace how

#endif // ARMYPAINTER_H
