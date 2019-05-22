#include "graphentitycontroller.h"

#include <QQmlEngine>

#include <boost/signals2.hpp>

#include "../../model/entities/graphentity.h"
#include "../conversion/converter.h"

#include <iostream>

namespace how {
namespace ui {

GraphEntityController::GraphEntityController(
    model::GraphEntityManager *graphEntityManagerPtr)
    : graphEntityManagerPtr(graphEntityManagerPtr) {}

void GraphEntityController::progressAll(float deltaTime) {
  this->graphEntityManagerPtr->progressAll(deltaTime);
}

void GraphEntityController::mousePressedOnGraphEntityPainter(
    QMouseEvent *event, std::shared_ptr<model::GraphEntity> graphEntityPtr) {
  switch (event->button()) {
  case Qt::LeftButton:
    this->onGraphEntitySelected(graphEntityPtr);
    break;
  case Qt::RightButton:
    this->onGraphEntityTargeted(graphEntityPtr);
    break;
  default:
    event->ignore();
    break;
  }
}

QRect GraphEntityController::getWorldBounds() const {
  return convert(this->graphEntityManagerPtr->getBounds());
}

void GraphEntityController::onGraphEntitySelected(
    std::shared_ptr<model::GraphEntity> graphEntityPtr) {
  this->selectionManager.setSelection(graphEntityPtr.get());
}

void GraphEntityController::onGraphEntityTargeted(
    std::shared_ptr<model::GraphEntity> graphEntityPtr) {
  if (this->selectionManager.hasSelection()) {
    auto *selection = this->selectionManager.getSelection();
    this->graphEntityManagerPtr->addGraphEntityPositionChange(
        selection, graphEntityPtr.get());
  }
}

} // namespace ui
} // namespace how
