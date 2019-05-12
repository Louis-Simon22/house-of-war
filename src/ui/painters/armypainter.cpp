#include "armypainter.h"

namespace how {
namespace ui {

ArmyPainter::ArmyPainter(const ArmyWrapper &armyWrapper)
    : EntityPainter(), armyWrapper(armyWrapper) {}

ArmyPainter::~ArmyPainter() {}

QSGNode *ArmyPainter::updatePaintNode(QSGNode *oldNode,
                                      QQuickItem::UpdatePaintNodeData *) {
  return oldNode;
}

} // namespace ui
} // namespace how
