#ifndef ARMIESITERATOR_H
#define ARMIESITERATOR_H

#include "../managers/entitiesmanager.h"

namespace how {
namespace model {

void iterateMovement(EntitiesManager &entitiesManager);
void iterateTiles(EntitiesManager &entitiesManager);
void iterateArmies(EntitiesManager &entitiesManager);

} // namespace model
} // namespace how

#endif // ARMIESITERATOR_H
