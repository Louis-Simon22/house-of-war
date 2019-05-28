#include "maincontroller.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>

#include "../painters/armypainter.h"
#include "../painters/characterpainter.h"
#include "../painters/segmentspainter.h"
#include "../painters/voronoicellpainter.h"

#include <boost/signals2.hpp>

namespace how {
namespace ui {

MainController::MainController() : modelThreadManager(), modelController() {
  connect(&modelThreadManager, &ModelThreadManager::iterate,
          &this->modelController, &ModelController::iterateModel,
          Qt::QueuedConnection);
  // TODO move graphentitycontroller to this class
  this->modelThreadManager.registerQObjectOnThread(
      this->modelController.getGraphEntityControllerPtr());
  this->modelThreadManager.registerQObjectOnThread(&this->modelController);
  connect(&this->modelThreadManager, &ModelThreadManager::iterate,
          &this->modelController, &ModelController::iterateModel,
          Qt::QueuedConnection);
}

void MainController::generateMapElements(QQuickItem *parent) {
  auto *graphEntityManagerPtr =
      this->modelController.getGraphEntityManagerPtr();
  auto &armyPtrs = graphEntityManagerPtr->getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    auto *armyPainter = new ArmyPainter(parent, armyPtr);
    this->bindPainterClickSignalAndSetObjectOwnership(armyPainter);
  }

  auto &characterPtrs = graphEntityManagerPtr->getCharacterPtrs();
  for (auto &characterPtr : characterPtrs) {
    auto *characterPainter = new CharacterPainter(parent, characterPtr);
    this->bindPainterClickSignalAndSetObjectOwnership(characterPainter);
  }

  auto &voronoiCellPtrs = graphEntityManagerPtr->getVoronoiCellPtrs();
  for (auto &voronoiCellPtr : voronoiCellPtrs) {
    auto *voronoiCellPainter = new VoronoiCellPainter(parent, voronoiCellPtr);
    this->bindPainterClickSignalAndSetObjectOwnership(voronoiCellPainter);
  }

  auto *delaunaySegmentsPainter = new SegmentsPainter(
      parent,
      this->modelController.getGraphEntityManagerPtr()->getDelaunaySegments());
  QQmlEngine::setObjectOwnership(delaunaySegmentsPainter,
                                 QQmlEngine::JavaScriptOwnership);
  delaunaySegmentsPainter->setVisible(true);
  auto *voronoiSegmentsPainter = new SegmentsPainter(
      parent,
      this->modelController.getGraphEntityManagerPtr()->getVoronoiSegments());
  QQmlEngine::setObjectOwnership(voronoiSegmentsPainter,
                                 QQmlEngine::JavaScriptOwnership);
  voronoiSegmentsPainter->setVisible(false);
}

ModelController *MainController::getModelController() {
  return &this->modelController;
}

void MainController::bindPainterClickSignalAndSetObjectOwnership(
    PainterItem *entityPainter) {
  auto *graphEntityControllerPtr =
      this->modelController.getGraphEntityControllerPtr();
  connect(entityPainter, &PainterItem::mousePressedOnGraphEntityPainter,
          graphEntityControllerPtr,
          &GraphEntityController::mousePressedOnGraphEntityPainter,
          Qt::QueuedConnection);
  QQmlEngine::setObjectOwnership(entityPainter,
                                 QQmlEngine::JavaScriptOwnership);
}

} // namespace ui
} // namespace how
