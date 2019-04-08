#include "characterscontroller.h"

#include "../../model/entities/movement/graphmovement.h"
#include "../../model/entities/movement/movementcalculator.h"

namespace how {
namespace ui {

CharactersController::CharactersController() : QObject(nullptr) {}
CharactersController::CharactersController(
    model::EntityChangeManager *entityChangeManagerPtr,
    model::WorldData *worldDataPtr, model::CharacterData *characterDataPtr,
    CharactersModel *charactersModelPtr)
    : QObject(nullptr), entityChangeManagerPtr(entityChangeManagerPtr),
      worldDataPtr(worldDataPtr), characterDataPtr(characterDataPtr),
      charactersModelPtr(charactersModelPtr) {}

void CharactersController::addMoveOrder(int characterIndex,
                                        int voronoiCellIndex) {
  auto *graphMovement =
      model::calculateMovement(this->worldDataPtr->getGraph(),
                               this->characterDataPtr->getCharacter(
                                   static_cast<std::size_t>(characterIndex)),
                               static_cast<std::size_t>(voronoiCellIndex));
  graphMovement->changeSignal.connect(
      ::boost::bind(&EntityModel::entityChanged, this->charactersModelPtr, _1));
  this->entityChangeManagerPtr->addEntityChange(graphMovement);
}

void CharactersController::iterateAllChanges() {
  this->entityChangeManagerPtr->progressAll(1.0f);
}
} // namespace ui
} // namespace how
