#include "maincontroller.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>

#include "../painters/armypainter.h"
#include "../painters/characterpainter.h"
#include "../painters/voronoicellpainter.h"

namespace how {
namespace ui {

MainController::MainController()
    : modelManager(), modelThreadManager(), entityControllerPtr(),
      worldManagerWrapperPtr() {}

void MainController::newModel(int width, int height,
                              float minimumVoronoiCellDistance,
                              int randomSeed) {
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(config);
  this->worldManagerWrapperPtr.reset(
      new WorldController(this->modelManager.getWorldManagerPtr()));
  this->entityControllerPtr.reset(
      new EntityController(this->modelManager.getGraphEntityManager()));
  this->newModelGenerated();
}

void MainController::instantiateUiElements(QQuickItem *parent) {
  auto &armies = modelManager.getArmies();

  for (auto &army : armies) {
    this->bindEntityPainter(parent, new ArmyPainter(army));
  }
  auto &characters = this->modelManager.getCharacters();
  for (auto &character : characters) {
    this->bindEntityPainter(parent, new CharacterPainter(character));
  }
  auto *worldManagerPtr = this->modelManager.getWorldManagerPtr();
  types::graph_vertex_iterator_t vertexItBegin, vertexItEnd;
  std::tie(vertexItBegin, vertexItEnd) = worldManagerPtr->getVertexIterators();
  for (auto vertexIt = vertexItBegin; vertexIt != vertexItEnd; vertexIt++) {
    const auto vertexDesc = *vertexIt;
    model::VoronoiCell &voronoiCell =
        worldManagerPtr->getVoronoiCellByDesc(vertexDesc);
    this->bindEntityPainter(parent, new VoronoiCellPainter(voronoiCell));
  }
}

void MainController::bindEntityPainter(QQuickItem *parent,
                                       EntityPainter *entityPainter) {
  entityPainter->setParentItem(parent);
  entityPainter->setParent(parent);
  QQmlEngine::setObjectOwnership(entityPainter,
                                 QQmlEngine::JavaScriptOwnership);
  auto *mouseAreaItem = instantiateMouseAreaItem(entityPainter);

  const auto &graphEntity = entityPainter->getGraphEntity();
//  graphEntity.visualChangedSignal.connect(
//      ::boost::bind(&EntityPainter::update, entityPainter, _1));
//  graphEntity.dimensionsChangedSignal.connect(
//      ::boost::bind(&EntityPainter::updateDimensions, entityPainter, _1));
//    graphEntity.dimensionsChangedSignal.connect(&entityPainter->update);
//  graphEntity.destructionSignal.connect(
//      ::boost::bind(&QQuickItem::deleteLater, entityPainter, _1));
}

QQuickItem *MainController::instantiateMouseAreaItem(QQuickItem *parent) {
  auto *qmlEngine = QQmlEngine::contextForObject(parent)->engine();
  QQmlComponent component(
      qmlEngine,
      QUrl::fromLocalFile("../../../qml/game/components/GenericMouseArea.qml"));
  auto *mouseAreaObject = component.create();
  QQuickItem *mouseAreaItem = qobject_cast<QQuickItem *>(mouseAreaObject);
  mouseAreaItem->setParentItem(parent);
  mouseAreaItem->setParent(parent);
  QQmlEngine::setObjectOwnership(mouseAreaObject,
                                 QQmlEngine::JavaScriptOwnership);
  return mouseAreaItem;
}

EntityController *MainController::getEntityController() {
  return this->entityControllerPtr.get();
}

WorldController *MainController::getWorldManagerWrapper() {
  return this->worldManagerWrapperPtr.get();
}

} // namespace ui
} // namespace how
