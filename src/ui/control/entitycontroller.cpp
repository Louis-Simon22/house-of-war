#include "entitycontroller.h"

#include <QQmlEngine>

#include <boost/signals2.hpp>

#include "../../model/entities/graphentity.h"
#include "../../model/entities/graphentitypositionchange.h"
#include "../../model/operations/pathfindingoperations.h"

namespace how {
namespace ui {

EntityController::EntityController(
    model::EntityChangeManager *entityChangeManagerPtr,
    std::vector<std::unique_ptr<EntityWrapper>> *entityWrappersPtr)
    : selectionManager(), entityChangeManagerPtr(entityChangeManagerPtr),
      entityWrappersPtr(entityWrappersPtr) {}

QQuickItem *EntityController::createEntityWrapperPainterAtIndex(int index) {
  const auto &entityWrapperPtr =
      this->entityWrappersPtr->operator[](static_cast<std::size_t>(index));
  auto *entityPainter = entityWrapperPtr->createEntityPainter();
  //  entityPainter->setZ(entityWrapperPtr->getLayer());
  connect(entityWrapperPtr.get(), &EntityWrapper::updateEntityPainter,
          entityPainter, &QQuickItem::update);
  QQmlEngine::setObjectOwnership(entityPainter,
                                 QQmlEngine::JavaScriptOwnership);
  return entityPainter;
}

void EntityController::onEntityWrapperClicked(int entityWrapperIndexInt,
                                              int mouseButton) {
  const auto entityWrapperIndex =
      static_cast<std::size_t>(entityWrapperIndexInt);
  auto *clickedEntityWrapper =
      this->entityWrappersPtr->operator[](entityWrapperIndex).get();
  switch (mouseButton) {
  case Qt::LeftButton:
    this->selectionManager.selectEntity(clickedEntityWrapper);
    break;
  case Qt::RightButton:
    if (this->selectionManager.hasSelection()) {
      this->selectionManager.getSelection()->onEntityWrapperTargeted(
          clickedEntityWrapper);
    }
    break;
  }
}

void EntityController::iterateAllChanges(float deltaTime) {
  this->entityChangeManagerPtr->progressAll(deltaTime);
}
} // namespace ui
} // namespace how
