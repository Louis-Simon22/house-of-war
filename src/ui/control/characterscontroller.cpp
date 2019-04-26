#include "characterscontroller.h"

#include "../../model/entities/graphentity.h"
#include "../../model/entities/graphentitypositionchange.h"
#include "../../model/operations/pathfindingoperations.h"

namespace how {
namespace ui {

CharactersController::CharactersController() : QObject(nullptr) {}

CharactersController::CharactersController(
    model::EntityChangeManager *entityChangeManagerPtr,
    model::WorldManager *WorldManagerPtr,
    model::GraphEntityManager *graphEntityManagerPtr,
    CharactersModel *charactersModelPtr)
    : QObject(nullptr), entityChangeManagerPtr(entityChangeManagerPtr),
      worldManagerPtr(WorldManagerPtr),
      graphEntityManagerPtr(graphEntityManagerPtr),
      charactersModelPtr(charactersModelPtr) {}

void CharactersController::addMoveOrder(int characterIndex,
                                        int voronoiCellIndex) {
  auto &character = this->graphEntityManagerPtr->getCharacter(
      static_cast<std::size_t>(characterIndex));
  auto destinationVertexDesc = static_cast<std::size_t>(voronoiCellIndex);
  if (character.getCurrentVertexDesc() != destinationVertexDesc) {
    auto *graphMovement = model::graphEntityPathfinding(
        this->worldManagerPtr->getGraph(), character, destinationVertexDesc);
    graphMovement->changeSignal.connect(::boost::bind(
        &EntityModel::entityChanged, this->charactersModelPtr, _1));
    this->entityChangeManagerPtr->addEntityChange(graphMovement);
  }
}

void CharactersController::iterateAllChanges(float deltaTime) {
  this->entityChangeManagerPtr->progressAll(deltaTime);
}
} // namespace ui
} // namespace how
