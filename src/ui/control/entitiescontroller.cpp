#include "entitiescontroller.h"

#include <QQmlEngine>

#include "../conversion/converter.h"
#include "../items/armyitem.h"
#include "../items/voronoicellitem.h"
#include "../painters/segmentspainter.h"

namespace how {
namespace ui {

EntitiesController::EntitiesController(model::ModelManager &modelManager)
    : modelManager(modelManager),
      entitiesManager(modelManager.getEntitiesManager()), armyBindings(),
      voronoiCellBindings() {}

void EntitiesController::generateMapItems(QQuickItem *parent) {
  auto *entitiesManager = this->modelManager.getEntitiesManager();
  auto &armyPtrs = entitiesManager->getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    auto *armyItem = new ArmyItem(armyPtr, parent);
    QQmlEngine::setObjectOwnership(armyItem, QQmlEngine::JavaScriptOwnership);
  }

  auto &voronoiCellPtrs = entitiesManager->getVoronoiCellPtrs();
  for (auto &voronoiCellPtr : voronoiCellPtrs) {
    auto *voronoiCellItem = new VoronoiCellItem(voronoiCellPtr, parent);
    QQmlEngine::setObjectOwnership(voronoiCellItem,
                                   QQmlEngine::JavaScriptOwnership);
  }

  auto *delaunaySegmentsPainter = new SegmentsPainter(
      parent,
      this->modelManager.getDelaunayVoronoiGraphPtr()->getDelaunaySegments());
  QQmlEngine::setObjectOwnership(delaunaySegmentsPainter,
                                 QQmlEngine::JavaScriptOwnership);
  delaunaySegmentsPainter->setVisible(true);
  auto *voronoiSegmentsPainter = new SegmentsPainter(
      parent,
      this->modelManager.getDelaunayVoronoiGraphPtr()->getVoronoiSegments());
  QQmlEngine::setObjectOwnership(voronoiSegmentsPainter,
                                 QQmlEngine::JavaScriptOwnership);
  voronoiSegmentsPainter->setVisible(false);
}

ArmyBindings *EntitiesController::getArmyBindings() {
  return &this->armyBindings;
}

VoronoiCellBindings *EntitiesController::getVoronoiCellBindings() {
  return &this->voronoiCellBindings;
}

} // namespace ui
} // namespace how
