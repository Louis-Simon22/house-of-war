#include "graphentityitem.h"

namespace how {
namespace ui {

GraphEntityItem::GraphEntityItem(QQuickItem *parent,
                       std::shared_ptr<model::GraphEntity> graphEntityPtr)
    : QQuickItem(parent), graphEntityPtr(graphEntityPtr) {
  this->updateAcceptedMouseButtons();
  this->graphEntityPtr->visualChangedSignal.connect(
      ::boost::bind(&GraphEntityItem::updateOnGuiThread, this));
  connect(this, &GraphEntityItem::updateOnGuiThread, this, &QQuickItem::update,
          Qt::QueuedConnection);
  this->graphEntityPtr->dimensionsChangedSignal.connect(
      ::boost::bind(&GraphEntityItem::updateDimensionsOnGuiThread, this));
  connect(this, &GraphEntityItem::updateDimensionsOnGuiThread, this,
          &GraphEntityItem::updateDimensions, Qt::QueuedConnection);
}

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
