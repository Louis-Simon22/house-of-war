#ifndef ARMIESITERATOR_H
#define ARMIESITERATOR_H

#include "../managers/graphmanager.h"
#include "../managers/entitiesmanager.h"

namespace how {
namespace model {

void iterateArmies(EntitiesManager &entitiesManager,
                   GraphManager *delaunayVoronoiGraph);

} // namespace model
} // namespace how

#endif // ARMIESITERATOR_H
