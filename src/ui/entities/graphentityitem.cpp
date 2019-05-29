#include "graphentityitem.h"

namespace how {
namespace ui {

GraphEntityItem::GraphEntityItem(
    std::shared_ptr<model::GraphEntity> graphEntityPtr,
    QQuickItem *visualParent, QObject *memoryParent)
    : QQuickItem(nullptr), graphEntityPtr(graphEntityPtr) {
  this->setParent(memoryParent);
  this->setParentItem(visualParent);
  this->updateAcceptedMouseButtons();
  this->graphEntityPtr->changedSignal.connect(
      ::boost::bind(&GraphEntityItem::updateOnGuiThread, this));
  connect(this, &GraphEntityItem::updateOnGuiThread, this,
          &GraphEntityItem::onGraphEntityUpdated, Qt::QueuedConnection);
}

GraphEntityItem::~GraphEntityItem() {}

void GraphEntityItem::mousePressEvent(QMouseEvent *event) {
  const auto mappedPoint =
      this->mapToItem(this->parentItem(), QPointF(event->x(), event->y()));
  if (this->graphEntityPtr->isWithinSelectionArea(
          static_cast<float>(mappedPoint.x()),
          static_cast<float>(mappedPoint.y()))) {
    this->mousePressedOnGraphEntityPainter(event, this->graphEntityPtr.get());
  } else {
    event->ignore();
  }
}

void GraphEntityItem::updateAcceptedMouseButtons() {
  QFlags<Qt::MouseButton> acceptedMouseButtons = Qt::NoButton;
  if (this->graphEntityPtr->isSelectable()) {
    acceptedMouseButtons |= Qt::LeftButton;
  }
  if (this->graphEntityPtr->isTargetable()) {
    acceptedMouseButtons |= Qt::RightButton;
  }
  this->setAcceptedMouseButtons(acceptedMouseButtons);
}

} // namespace ui
} // namespace how
