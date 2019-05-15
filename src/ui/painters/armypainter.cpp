#include "armypainter.h"

namespace how {
namespace ui {

ArmyPainter::ArmyPainter(model::Army &army)
    : EntityPainter(army), army(army) {}

ArmyPainter::~ArmyPainter() {}

QSGNode *ArmyPainter::updatePaintNode(QSGNode *oldNode,
                                      QQuickItem::UpdatePaintNodeData *) {
  return oldNode;
}

} // namespace ui
} // namespace how
