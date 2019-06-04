#include "interactiveentityitem.h"

namespace how {
namespace ui {

InteractiveEntityItem::InteractiveEntityItem(
    std::shared_ptr<model::InteractiveEntity> interactiveEntityPtr,
    QQuickItem *parent)
    : EntityItem(interactiveEntityPtr, parent),
      interactiveEntityPtr(interactiveEntityPtr) {
  this->updateAcceptedMouseButtons();
}

InteractiveEntityItem::~InteractiveEntityItem() {}

void InteractiveEntityItem::mousePressEvent(QMouseEvent *event) {
  const auto mappedPoint =
      this->mapToItem(this->parentItem(), QPointF(event->x(), event->y()));
  if (this->interactiveEntityPtr->isWithinSelectionArea(
          static_cast<float>(mappedPoint.x()),
          static_cast<float>(mappedPoint.y()))) {
    this->mousePressedOnGraphEntityPainter(event,
                                           this->interactiveEntityPtr.get());
  } else {
    event->ignore();
  }
}

void InteractiveEntityItem::updateAcceptedMouseButtons() {
  QFlags<Qt::MouseButton> acceptedMouseButtons = Qt::NoButton;
  if (this->interactiveEntityPtr->isSelectable()) {
    acceptedMouseButtons |= Qt::LeftButton;
  }
  if (this->interactiveEntityPtr->isTargetable()) {
    acceptedMouseButtons |= Qt::RightButton;
  }
  this->setAcceptedMouseButtons(acceptedMouseButtons);
}

} // namespace ui
} // namespace how
