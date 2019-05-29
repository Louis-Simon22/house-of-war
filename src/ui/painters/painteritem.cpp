#include "painteritem.h"

namespace how {
namespace ui {

PainterItem::PainterItem(QQuickItem *parent) : QQuickItem(parent) {
  this->setAntialiasing(true);
  this->setFlag(QQuickItem::ItemHasContents, true);
  connect(this, &PainterItem::updateOnGuiThread, this, &PainterItem::update,
          Qt::QueuedConnection);
}

PainterItem::~PainterItem() {}

} // namespace ui
} // namespace how
