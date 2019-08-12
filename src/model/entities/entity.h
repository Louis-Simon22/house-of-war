#ifndef ENTITY_H
#define ENTITY_H

#include "../../lib/nod/include/nod/nod.hpp"

#include "../modeltypes.h"

namespace how {
namespace model {
class EntityPositionChange;

class Entity {
public:
  using change_signal_t = ::nod::signal<void()>;

public:
  Entity(const Entity *parent);
  Entity(types::layer_t layer, const Entity *parent = nullptr);
  Entity(types::layer_t layer, types::point_t position,
         const Entity *parent = nullptr);
  virtual ~Entity() = 0;

public:
  void progressEntityPositionChange();

public:
  types::layer_t getLayer() const;
  const types::point_t &getPosition() const;
  types::coordinate_t getPosX() const;
  types::coordinate_t getPosY() const;
  types::coordinate_t getAbsolutePosX() const;
  types::coordinate_t getAbsolutePosY() const;
  types::point_t getAbsolutePosition() const;
  void setPosition(const types::point_t &position);
  void setEntityPositionChange(EntityPositionChange *entityPositionChange);

public:
  change_signal_t changeSignal;

protected:
  const Entity *parent;

private:
  types::layer_t layer;
  types::point_t position;
  std::unique_ptr<EntityPositionChange> entityPositionChangePtr;
};
} // namespace model
} // namespace how

#include "./entitypositionchange.h"

#endif // ENTITY_H
