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

MainController::MainController()
    : modelManager(), modelThreadManager(), graphEntityControllerPtr() {}

void MainController::newModel(int width, int height,
                              float minimumVoronoiCellDistance,
                              int randomSeed) {
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(config);
  this->graphEntityControllerPtr.reset(
      new GraphEntityController(this->modelManager.getGraphEntityManagerPtr()));
  this->newModelGenerated();
//  this->modelThreadManager.registerQObjectOnThread(
//      graphEntityControllerPtr.get());
  connect(&modelThreadManager, &ModelThreadManager::iteration,
          this->graphEntityControllerPtr.get(),
          &GraphEntityController::progressAll, Qt::QueuedConnection);
  this->modelThreadManager.resumeIterations();
}

void MainController::instantiateUiElements(QQuickItem *parent) {
  auto *graphEntityManagerPtr = this->modelManager.getGraphEntityManagerPtr();
  auto &armyPtrs = graphEntityManagerPtr->getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    auto *armyPainter = new ArmyPainter(parent, armyPtr);
    this->bindClickSignalAndSetObjectOwnership(armyPainter);
  }

  auto &characterPtrs = graphEntityManagerPtr->getCharacterPtrs();
  for (auto &characterPtr : characterPtrs) {
    auto *characterPainter = new CharacterPainter(parent, characterPtr);
    this->bindClickSignalAndSetObjectOwnership(characterPainter);
  }

  auto &voronoiCellPtrs = graphEntityManagerPtr->getVoronoiCellPtrs();
  std::size_t greg = 0;
  for (auto &voronoiCellPtr : voronoiCellPtrs) {
    auto *voronoiCellPainter = new VoronoiCellPainter(parent, voronoiCellPtr);
    this->bindClickSignalAndSetObjectOwnership(voronoiCellPainter);
    voronoiCellPainter->index = greg++;
  }

  auto *delaunaySegmentsPainter = new SegmentsPainter(
      parent,
      this->modelManager.getGraphEntityManagerPtr()->getDelaunaySegments());
  QQmlEngine::setObjectOwnership(delaunaySegmentsPainter,
                                 QQmlEngine::JavaScriptOwnership);
  delaunaySegmentsPainter->setVisible(true);
  auto *voronoiSegmentsPainter = new SegmentsPainter(
      parent,
      this->modelManager.getGraphEntityManagerPtr()->getVoronoiSegments());
  QQmlEngine::setObjectOwnership(voronoiSegmentsPainter,
                                 QQmlEngine::JavaScriptOwnership);
  voronoiSegmentsPainter->setVisible(false);
}

GraphEntityController *MainController::getGraphEntityController() {
  return this->graphEntityControllerPtr.get();
}

void MainController::bindClickSignalAndSetObjectOwnership(
    EntityPainter *entityPainter) {
  connect(entityPainter, &EntityPainter::mousePressedOnGraphEntityPainter,
          this->graphEntityControllerPtr.get(),
          &GraphEntityController::mousePressedOnGraphEntityPainter,
          Qt::QueuedConnection);
  QQmlEngine::setObjectOwnership(entityPainter,
                                 QQmlEngine::JavaScriptOwnership);
}

} // namespace ui
} // namespace how
