#ifndef ENTITYPOSITIONCHANGE_H
#define ENTITYPOSITIONCHANGE_H

#include "./entitychange.h"
#include "./voronoicell.h"

namespace how {
namespace model {
class EntityPositionChange : public EntityChange {
public:
  EntityPositionChange(Entity *entity,
                       std::vector<const VoronoiCell *> destinations);
  ~EntityPositionChange() override;

public:
  bool progress() override;

private:
  Entity *entity;
  std::vector<const VoronoiCell *> destinations;
  std::size_t currentDestinationIndex;
};
} // namespace model
} // namespace how

#endif // ENTITYPOSITIONCHANGE_H
