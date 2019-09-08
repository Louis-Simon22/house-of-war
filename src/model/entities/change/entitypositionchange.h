#ifndef ENTITYPOSITIONCHANGE_H
#define ENTITYPOSITIONCHANGE_H

#include <vector>

#include "../modeltypes.h"

namespace how {
namespace model {
class Entity;

class EntityPositionChange {
public:
  EntityPositionChange(Entity *entity,
                       std::vector<types::point_t> destinations);
  ~EntityPositionChange();

public:
  std::vector<types::point_t> getPathAsRelativePoints() const;
  bool progress();
  bool isDone();

private:
  Entity *entity;
  std::vector<types::point_t> destinations;
  std::size_t currentDestinationIndex;
};
} // namespace model
} // namespace how

#include "./entity.h"

#endif // ENTITYPOSITIONCHANGE_H
