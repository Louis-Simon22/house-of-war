#include "modelcontroller.h"

#include <QQmlEngine>

#include "../../model/generation/worldgenerationconfig.h"
#include "../conversion/converter.h"
#include "../items/armyitem.h"
#include "../items/voronoicellitem.h"
#include "../painters/segmentspainter.h"

namespace how {
namespace ui {

ModelController::ModelController(QObject *parent)
    : QObject(parent), modelManager(), entitiesController(this->modelManager) {}

void ModelController::newModel(int width, int height,
                               float minimumVoronoiCellDistance,
                               int randomSeed) {
  auto config = model::WorldGenerationConfig(
      0, 0, width, height, minimumVoronoiCellDistance,
      static_cast<std::uint32_t>(randomSeed));
  this->modelManager.newModel(config);
  this->newModelGenerated();
}

void ModelController::iterateModel() { this->modelManager.iterateModel(); }

// TODO bouger ca dans le entities controller
void ModelController::generateMapItems(QQuickItem *parent) {
  auto *entitiesManager = this->modelManager.getEntitiesManager();
  auto &armyPtrs = entitiesManager->getArmyPtrs();
  for (auto &armyPtr : armyPtrs) {
    auto *armyItem = new ArmyItem(armyPtr, parent);
    this->bindEntityItemClickSignalAndSetObjectOwnership(armyItem);
  }

  auto &voronoiCellPtrs = entitiesManager->getVoronoiCellPtrs();
  for (auto &voronoiCellPtr : voronoiCellPtrs) {
    auto *voronoiCellItem = new VoronoiCellItem(voronoiCellPtr, parent);
    this->bindEntityItemClickSignalAndSetObjectOwnership(voronoiCellItem);
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

void ModelController::bindEntityItemClickSignalAndSetObjectOwnership(
    InteractiveEntityItem *interactiveEntityItem) {
  connect(interactiveEntityItem,
          &InteractiveEntityItem::mousePressedOnGraphEntityPainter,
          &this->entitiesController,
          &EntitiesController::mousePressedOnGraphEntityPainter);
  QQmlEngine::setObjectOwnership(interactiveEntityItem,
                                 QQmlEngine::JavaScriptOwnership);
}

QRect ModelController::getWorldBounds() const {
  return convert(this->modelManager.getDelaunayVoronoiGraphPtr()->getBounds());
}

EntitiesController *ModelController::getEntitiesController() {
  return &this->entitiesController;
}

} // namespace ui
} // namespace how
