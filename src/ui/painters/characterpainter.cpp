#include "characterpainter.h"

namespace how {
namespace ui {

CharacterPainter::CharacterPainter(const model::Character &character)
    : character(character) {}

CharacterPainter::~CharacterPainter() {}

QSGNode *CharacterPainter::updatePaintNode(QSGNode *oldNode,
                                           QQuickItem::UpdatePaintNodeData *) {
  return oldNode;
}

} // namespace ui
} // namespace how
