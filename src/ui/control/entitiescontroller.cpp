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
  selectionManager->armySelectedSignal.connect(std::bind(
      &ArmyBindings::bindArmy, &this->armyBindings, std::placeholders::_1));
  selectionManager->tileSelectedSignal.connect(std::bind(
      &TileBindings::bindTile, &this->tileBindings, std::placeholders::_1));
}

void EntitiesController::generateMapItems(QQuickItem *parent) {
  auto *entitiesManager = this->modelManager.getEntitiesManager();
  auto &armyPtrs = entitiesManager->getPlayers()[0].getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    new ArmyItem(armyPtr.get(), parent);
  }

  auto &tilePtrs = entitiesManager->getTilePtrs();
  for (auto &tilePtr : tilePtrs) {
    auto *tileItem =
        new TileItem(tilePtr.get(), &this->tilesController, parent);
    connect(&this->tilesController,
            &TilesController::onTileDisplayStatusChanged, tileItem,
            &TileItem::onTileDisplayStatusChanged);
  }

  auto *delaunaySegmentsPainter = new SegmentsPainter(
      this->entitiesManager->getUniqueDelaunaySegments(), parent);
  delaunaySegmentsPainter->setVisible(true);
  auto *voronoiSegmentsPainter = new SegmentsPainter(
      this->entitiesManager->getUniqueVoronoiSegments(), parent);
  voronoiSegmentsPainter->setVisible(false);
}

const TilesController *EntitiesController::getTilesController() const {
  return &this->tilesController;
}

TilesController *EntitiesController::getTilesController() {
  return &this->tilesController;
}

ArmyBindings *EntitiesController::getArmyBindings() {
  return &this->armyBindings;
}

TileBindings *EntitiesController::getTileBindings() {
  return &this->tileBindings;
}

} // namespace ui
} // namespace how
