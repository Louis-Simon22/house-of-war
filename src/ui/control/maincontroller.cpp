#include "maincontroller.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>

#include "../painters/armypainter.h"
#include "../painters/characterpainter.h"
#include "../painters/voronoicellpainter.h"

#include <boost/signals2.hpp>

namespace how {
namespace ui {

MainController::MainController()
    : modelManager(), modelThreadManager(), entityControllerPtr(),
      worldControllerPtr() {}

void MainController::newModel(int width, int height,
                              float minimumVoronoiCellDistance,
                              int randomSeed) {
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(config);
  this->worldControllerPtr.reset(
      new WorldController(this->modelManager.getWorldManagerPtr()));
  this->entityControllerPtr.reset(
      new EntityController(this->modelManager.getGraphEntityManager()));
  this->newModelGenerated();
}

void MainController::instantiateUiElements(QQuickItem *parent) {
  auto &armies = modelManager.getArmies();
  for (auto &army : armies) {
    auto *armyPainter = new ArmyPainter(army);
    this->bindEntityPainter(parent, armyPainter);
    auto &graphEntity = armyPainter->getGraphEntity();
    graphEntity.changeSignals.visualChangedSignal.connect(
        ::boost::bind(&QQuickItem::update, armyPainter));
    graphEntity.changeSignals.dimensionsChangedSignal.connect(
        ::boost::bind(&EntityPainter::updateDimensions, armyPainter));
    graphEntity.changeSignals.destructionSignal.connect(
        ::boost::bind(&QQuickItem::deleteLater, armyPainter));
  }

  auto &characters = this->modelManager.getCharacters();
  for (auto &character : characters) {
    auto characterPainter =
        boost::shared_ptr<CharacterPainter>(new CharacterPainter(character));
    this->bindEntityPainter(parent, characterPainter.get());
    auto &graphEntity = characterPainter->getGraphEntity();
    graphEntity.changeSignals.visualChangedSignal.connect(
        ::boost::bind(&QQuickItem::update, characterPainter));
    graphEntity.changeSignals.dimensionsChangedSignal.connect(
        ::boost::bind(&EntityPainter::updateDimensions, characterPainter));
    graphEntity.changeSignals.destructionSignal.connect(
        ::boost::bind(&QQuickItem::deleteLater, characterPainter));
  }

  auto *worldManagerPtr = this->modelManager.getWorldManagerPtr();
  types::graph_vertex_iterator_t vertexItBegin, vertexItEnd;
  std::tie(vertexItBegin, vertexItEnd) = worldManagerPtr->getVertexIterators();
  for (auto vertexIt = vertexItBegin; vertexIt != vertexItEnd; vertexIt++) {
    const auto vertexDesc = *vertexIt;
    model::VoronoiCell &voronoiCell =
        worldManagerPtr->getVoronoiCellByDesc(vertexDesc);
    auto *voronoiPainter = new VoronoiCellPainter(voronoiCell);
    this->bindEntityPainter(parent, voronoiPainter);
    auto &graphEntity = voronoiPainter->getGraphEntity();
    graphEntity.changeSignals.visualChangedSignal.connect(
        ::boost::bind(&QQuickItem::update, voronoiPainter));
    graphEntity.changeSignals.dimensionsChangedSignal.connect(
        ::boost::bind(&EntityPainter::updateDimensions, voronoiPainter));
    graphEntity.changeSignals.destructionSignal.connect(
        ::boost::bind(&QQuickItem::deleteLater, voronoiPainter));
  }
}

void MainController::bindEntityPainter(QQuickItem *parent,
                                       EntityPainter *entityPainter) {
  entityPainter->setParentItem(parent);
  entityPainter->setParent(parent);
  QQmlEngine::setObjectOwnership(entityPainter,
                                 QQmlEngine::JavaScriptOwnership);
}

EntityController *MainController::getEntityController() {
  return this->entityControllerPtr.get();
}

WorldController *MainController::getWorldController() {
  return this->worldControllerPtr.get();
}

} // namespace ui
} // namespace how
