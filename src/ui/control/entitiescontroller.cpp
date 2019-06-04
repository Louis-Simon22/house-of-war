#include "entitiescontroller.h"

#include "../conversion/converter.h"

namespace how {
namespace ui {

EntitiesController::EntitiesController(model::ModelManager &modelManager)
    : modelManager(modelManager),
      entitiesManager(modelManager.getEntitiesManager()), selectionManager() {}

void EntitiesController::mousePressedOnGraphEntityPainter(
    QMouseEvent *event, model::InteractiveEntity *graphEntity) {
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

void EntitiesController::onGraphEntitySelected(
    model::InteractiveEntity *graphEntity) {
  // TODO able to select voronoiCells and display their stats
  this->selectionManager.setSelection(graphEntity);
}

void EntitiesController::onGraphEntityTargeted(
    model::InteractiveEntity *graphEntity) {
  if (this->selectionManager.hasSelection()) {
    auto *selection = this->selectionManager.getSelection();
    this->modelManager.addGraphEntityPositionChange(selection, graphEntity);
  }
}

} // namespace ui
} // namespace how
