#include "entitypainter.h"

#include <boost/signals2.hpp>

#include <iostream>

namespace how {
namespace ui {
namespace {
namespace bs = ::boost::signals2;
}

EntityPainter::EntityPainter(QQuickItem *parent,
                             std::shared_ptr<model::GraphEntity> graphEntityPtr)
    : QQuickItem(parent), graphEntityPtr(graphEntityPtr) {
  this->setAntialiasing(true);
  this->setFlag(QQuickItem::ItemHasContents, true);
  this->updateAcceptedMouseButtons();
}

void EntityPainter::mousePressEvent(QMouseEvent *event) {
  const auto mappedPoint =
      this->mapToItem(this->parentItem(), QPointF(event->x(), event->y()));
  if (this->graphEntityPtr->isWithinSelectionArea(
          static_cast<float>(mappedPoint.x()),
          static_cast<float>(mappedPoint.y()))) {
    this->mousePressedOnGraphEntityPainter(event, this->graphEntityPtr);
  } else {
    event->ignore();
  }
}

// TODO connect a signal from the graph entity to this
void EntityPainter::updateAcceptedMouseButtons() {
  QFlags<Qt::MouseButton> acceptedMouseButtons = Qt::NoButton;
  if (this->graphEntityPtr->isSelectable()) {
    acceptedMouseButtons |= Qt::LeftButton;
  }
  if (this->graphEntityPtr->isTargetable()) {
    acceptedMouseButtons |= Qt::RightButton;
  }
  this->setAcceptedMouseButtons(acceptedMouseButtons);
}

EntityPainter::~EntityPainter() {}

} // namespace ui
} // namespace how
