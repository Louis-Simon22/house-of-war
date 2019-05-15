#include "entitycontroller.h"

#include <QQmlEngine>

#include <boost/signals2.hpp>

#include "../../model/entities/graphentity.h"
#include "../../model/entities/graphentitypositionchange.h"
#include "../../model/operations/pathfindingoperations.h"

#include <iostream>

namespace how {
namespace ui {

EntityController::EntityController(
    model::GraphEntityManager &graphEntityManager)
    : graphEntityManager(graphEntityManager) {}

void onGraphEntityClicked(model::GraphEntity *graphEntity, int mouseButton) {
  std::cout << "Greg" << std::endl;
}

void EntityController::iterateAllChanges(float deltaTime) {
  this->graphEntityManager.progressAll(deltaTime);
}

} // namespace ui
} // namespace how
