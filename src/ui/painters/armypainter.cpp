#include "armypainter.h"

namespace how {
namespace ui {

ArmyPainter::ArmyPainter(const model::Army &army) : army(army) {}

ArmyPainter::~ArmyPainter() {}

QSGNode *ArmyPainter::updatePaintNode(QSGNode *oldNode,
                                      QQuickItem::UpdatePaintNodeData *) {
  return oldNode;
}

} // namespace ui
} // namespace how
