#include "maincontroller.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>

#include "../entities/armyitem.h"
#include "../entities/voronoicellitem.h"
#include "../painters/segmentspainter.h"

namespace how {
namespace ui {

MainController::MainController()
    : modelThreadManager(new ModelThreadManager(this)),
      iterationTimerManager(new IterationTimerManager(this)),
      modelController(new ModelController(this)) {
  // TODO move model operations to another thread
  //  this->modelThreadManager.registerQObjectOnThread(&this->modelController);
  connect(this->iterationTimerManager, &IterationTimerManager::iterate,
          this->modelController, &ModelController::iterateModel,
          Qt::QueuedConnection);
}

void MainController::generateMapItems(QQuickItem *parent) {
  auto *graphEntityManagerPtr =
      this->modelController->getGraphEntityManagerPtr();
  auto &armyPtrs = graphEntityManagerPtr->getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    auto *armyItem = new ArmyItem(parent, armyPtr);
    this->bindGraphEntityItemClickSignalAndSetObjectOwnership(armyItem);
  }

  auto &voronoiCellPtrs = graphEntityManagerPtr->getVoronoiCellPtrs();
  for (auto &voronoiCellPtr : voronoiCellPtrs) {
    auto *voronoiCellItem = new VoronoiCellItem(parent, voronoiCellPtr);
    this->bindGraphEntityItemClickSignalAndSetObjectOwnership(voronoiCellItem);
  }

  auto *delaunaySegmentsPainter = new SegmentsPainter(
      parent,
      this->modelController->getGraphEntityManagerPtr()->getDelaunaySegments());
  QQmlEngine::setObjectOwnership(delaunaySegmentsPainter,
                                 QQmlEngine::JavaScriptOwnership);
  delaunaySegmentsPainter->setVisible(true);
  auto *voronoiSegmentsPainter = new SegmentsPainter(
      parent,
      this->modelController->getGraphEntityManagerPtr()->getVoronoiSegments());
  QQmlEngine::setObjectOwnership(voronoiSegmentsPainter,
                                 QQmlEngine::JavaScriptOwnership);
  voronoiSegmentsPainter->setVisible(false);
}

ModelController *MainController::getModelController() {
  return this->modelController;
}

void MainController::bindGraphEntityItemClickSignalAndSetObjectOwnership(
    GraphEntityItem *graphEntityItem) {
  auto *graphEntityControllerPtr =
      this->modelController->getGraphEntityControllerPtr();
  connect(graphEntityItem, &GraphEntityItem::mousePressedOnGraphEntityPainter,
          graphEntityControllerPtr,
          &GraphEntityController::mousePressedOnGraphEntityPainter,
          Qt::QueuedConnection);
  QQmlEngine::setObjectOwnership(graphEntityItem,
                                 QQmlEngine::JavaScriptOwnership);
}

} // namespace ui
} // namespace how
