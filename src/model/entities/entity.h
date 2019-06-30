#ifndef ENTITY_H
#define ENTITY_H

#include <boost/signals2.hpp>

#include "../modeltypes.h"

namespace how {
namespace model {
class EntityPositionChange;

class Entity {
public:
  using changed_signal_t = ::boost::signals2::signal<void()>;

public:
  Entity(const Entity *parent);
  Entity(types::layer_t layer, const Entity *parent = nullptr);
  Entity(types::layer_t layer, types::point_t position,
         const Entity *parent = nullptr);
  virtual ~Entity() = 0;

public:
  types::layer_t getLayer() const;
  const types::point_t &getPosition() const;
  types::coordinate_t getPosX() const;
  types::coordinate_t getPosY() const;
  types::coordinate_t getAbsolutePosX() const;
  types::coordinate_t getAbsolutePosY() const;
  types::point_t getAbsolutePosition() const;
  void setPosition(const types::point_t &position);
  void progressEntityPositionChange();
  void setEntityPositionChange(EntityPositionChange *entityPositionChange);

public:
  changed_signal_t changedSignal;

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
