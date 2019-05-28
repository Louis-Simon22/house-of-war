#include "graphentitycontroller.h"

#include "../../model/entities/graphentity.h"
#include "../conversion/converter.h"

namespace how {
namespace ui {

GraphEntityController::GraphEntityController(
    model::GraphEntityManager *graphEntityManagerPtr)
    : graphEntityManagerPtr(graphEntityManagerPtr) {}

void GraphEntityController::mousePressedOnGraphEntityPainter(
    QMouseEvent *event, model::GraphEntity *graphEntity) {
  switch (event->button()) {
  case Qt::LeftButton:
    this->onGraphEntitySelected(graphEntity);
    break;
  case Qt::RightButton:
    this->onGraphEntityTargeted(graphEntity);
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
    model::GraphEntity *graphEntity) {
  // TODO able to select voronoiCells and display their stats
  this->selectionManager.setSelection(graphEntity);
}

void GraphEntityController::onGraphEntityTargeted(
    model::GraphEntity *graphEntity) {
  if (this->selectionManager.hasSelection()) {
    auto *selection = this->selectionManager.getSelection();
    this->graphEntityManagerPtr->addGraphEntityPositionChange(selection,
                                                              graphEntity);
  }
}

} // namespace ui
} // namespace how
