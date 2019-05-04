#include "entitypainter.h"

namespace how {
namespace ui {

EntityPainter::EntityPainter(QQuickItem *parent) : QQuickItem(parent) {
  this->setAntialiasing(true);
  this->setFlag(QQuickItem::ItemHasContents, true);
}

EntityPainter::~EntityPainter() {}

} // namespace ui
} // namespace how
