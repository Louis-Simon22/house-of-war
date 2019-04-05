#include "characterscontroller.h"

#include "../../model/entities/movement/graphmovement.h"
#include "../../model/entities/movement/movementcalculator.h"

namespace how {
namespace ui {

CharactersController::CharactersController() {}
CharactersController::CharactersController(
    model::EntityChangeManager *movementManagerPtr, model::WorldData *worldDataPtr,
    model::CharacterData *characterDataPtr, CharactersModel *charactersModelPtr)
    : movementManagerPtr(movementManagerPtr), worldDataPtr(worldDataPtr),
      characterDataPtr(characterDataPtr),
      charactersModelPtr(charactersModelPtr) {}

void CharactersController::addMoveOrder(int characterIndex,
                                        int voronoiCellIndex) {
  auto *graphMovement =
      model::calculateMovement(this->worldDataPtr->getGraph(),
                               this->characterDataPtr->getCharacter(
                                   static_cast<std::size_t>(characterIndex)),
                               static_cast<std::size_t>(voronoiCellIndex));
  this->movementManagerPtr->addMovement(graphMovement);
}

void CharactersController::movementIteration() {
  this->movementManagerPtr->progressAll(1.0f);
}
} // namespace ui
} // namespace how

// TODO give the responsibility of notification to the movement object? Generalize it to a Modification object?
