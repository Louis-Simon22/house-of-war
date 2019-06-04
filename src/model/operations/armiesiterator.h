#ifndef ARMIESITERATOR_H
#define ARMIESITERATOR_H

#include "../managers/delaunayvoronoigraph.h"
#include "../managers/entitiesmanager.h"

namespace how {
namespace model {

void iterateArmies(EntitiesManager &entitiesManager,
                   DelaunayVoronoiGraph *delaunayVoronoiGraph);

} // namespace model
} // namespace how

#endif // ARMIESITERATOR_H
