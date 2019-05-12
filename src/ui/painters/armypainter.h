#ifndef ARMYPAINTER_H
#define ARMYPAINTER_H

#include "../wrappers/armywrapper.h"
#include "./entitypainter.h"

namespace how {
namespace ui {
class ArmyPainter : public EntityPainter {
public:
  ArmyPainter(const ArmyWrapper &armyWrapper);
  ~ArmyPainter() override;

public:
  QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
  const ArmyWrapper &armyWrapper;
};
} // namespace ui
} // namespace how

#endif // ARMYPAINTER_H
