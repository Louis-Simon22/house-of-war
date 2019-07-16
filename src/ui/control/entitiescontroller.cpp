#include "entitiescontroller.h"

#include <QQmlEngine>

#include "../conversion/converter.h"
#include "../items/armyitem.h"
#include "../items/tileitem.h"
#include "../painters/segmentspainter.h"

namespace how {
namespace ui {

EntitiesController::EntitiesController(model::ModelManager &modelManager)
    : modelManager(modelManager),
      entitiesManager(modelManager.getEntitiesManager()), armyBindings(),
      tileBindings(), tilesController() {
  auto *selectionManager = modelManager.getSelectionManager();
  selectionManager->armySelectedSignal.connect(
      ::boost::bind(&ArmyBindings::bindArmy, &this->armyBindings, _1));
  selectionManager->tileSelectedSignal.connect(
      ::boost::bind(&TileBindings::bindTile, &this->tileBindings, _1));
}

void EntitiesController::generateMapItems(QQuickItem *parent) {
  auto *entitiesManager = this->modelManager.getEntitiesManager();
  auto &armyPtrs = entitiesManager->getPlayers()[0].getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    auto *armyItem = new ArmyItem(armyPtr.get(), parent);
    QQmlEngine::setObjectOwnership(armyItem, QQmlEngine::JavaScriptOwnership);
  }

  auto &tilePtrs = entitiesManager->getTilePtrs();
  for (auto &tilePtr : tilePtrs) {
    auto *tileItem =
        new TileItem(tilePtr.get(), &this->tilesController, parent);
    connect(&this->tilesController,
            &TilesController::onTileDisplayStatusChanged, tileItem,
            &TileItem::onTileDisplayStatusChanged);
    QQmlEngine::setObjectOwnership(tileItem, QQmlEngine::JavaScriptOwnership);
  }

  auto *delaunaySegmentsPainter = new SegmentsPainter(
      this->modelManager.getDelaunayVoronoiGraph()->getDelaunaySegments(),
      parent);
  QQmlEngine::setObjectOwnership(delaunaySegmentsPainter,
                                 QQmlEngine::JavaScriptOwnership);
  delaunaySegmentsPainter->setVisible(true);
  auto *voronoiSegmentsPainter = new SegmentsPainter(
      this->modelManager.getDelaunayVoronoiGraph()->getVoronoiSegments(),
      parent);
  QQmlEngine::setObjectOwnership(voronoiSegmentsPainter,
                                 QQmlEngine::JavaScriptOwnership);
  voronoiSegmentsPainter->setVisible(false);
}

ArmyBindings *EntitiesController::getArmyBindings() {
  return &this->armyBindings;
}

TileBindings *EntitiesController::getTileBindings() {
  return &this->tileBindings;
}

TilesController *EntitiesController::getTilesController() {
  return &this->tilesController;
}

} // namespace ui
} // namespace how
