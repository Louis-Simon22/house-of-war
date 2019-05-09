#include "graphentitycontroller.h"

#include <QQmlEngine>

#include <boost/signals2.hpp>

#include "../../model/entities/graphentity.h"
#include "../../model/entities/graphentitypositionchange.h"
#include "../../model/operations/pathfindingoperations.h"

namespace how {
namespace ui {

GraphEntityController::GraphEntityController() : QObject(nullptr) {}

GraphEntityController::GraphEntityController(
    model::EntityChangeManager *entityChangeManagerPtr,
    std::vector<std::unique_ptr<EntityWrapper>> *entityWrappersPtr)
    : entityChangeManagerPtr(entityChangeManagerPtr),
      entityWrappersPtr(entityWrappersPtr) {}

QQuickItem *
GraphEntityController::createEntityWrapperPainterAtIndex(int index) {
  const auto &entityWrapperPtr =
      this->entityWrappersPtr->operator[](static_cast<std::size_t>(index));
  auto *entityPainter = entityWrapperPtr->createEntityPainter();
  entityPainter->setZ(entityWrapperPtr->getLayer());
  connect(entityWrapperPtr.get(), &EntityWrapper::updateEntityPainter,
          entityPainter, &EntityPainter::update);
  QQmlEngine::setObjectOwnership(entityPainter,
                                 QQmlEngine::JavaScriptOwnership);
  return entityPainter;
}

void GraphEntityController::addMoveOrder(int characterIndex,
                                         int voronoiCellIndex) {
  //  auto &character = this->graphEntityManagerPtr->getCharacter(
  //      static_cast<std::size_t>(characterIndex));
  //  auto destinationVertexDesc = static_cast<std::size_t>(voronoiCellIndex);
  //  if (character.getCurrentVertexDesc() != destinationVertexDesc) {
  //    auto *graphMovement = model::graphEntityPathfinding(
  //        this->worldManagerPtr->getGraph(), character,
  //        destinationVertexDesc);
  //    graphMovement->changeSignal.connect(::boost::bind(
  //        &EntityModel::entityChanged, this->charactersModelPtr, _1));
  //    this->entityChangeManagerPtr->addEntityChange(graphMovement);
  //  }
}

void GraphEntityController::iterateAllChanges(float deltaTime) {
  this->entityChangeManagerPtr->progressAll(deltaTime);
}
} // namespace ui
} // namespace how
