#include "painteritem.h"

#include <boost/signals2.hpp>

#include <iostream>

namespace how {
namespace ui {
namespace {
namespace bs = ::boost::signals2;
}

PainterItem::PainterItem(QQuickItem *parent)
    : QQuickItem(parent) {
  this->setAntialiasing(true);
  this->setFlag(QQuickItem::ItemHasContents, true);
}

} // namespace ui
} // namespace how
