#ifndef ENTITY_H
#define ENTITY_H

#include "../delaunaygraphtypes.h"
#include "../modeltypes.h"

namespace how {
namespace model {
class Entity {
public:
  Entity();
  Entity(types::point_t position);
  ~Entity();

  types::point_t position;
};
} // namespace model
} // namespace how

#endif // ENTITY_H
