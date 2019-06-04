#ifndef INTERACTIVEENTITY_H
#define INTERACTIVEENTITY_H

#include "../modeltypes.h"
#include "./entity.h"

namespace how {
namespace model {
class InteractiveEntity : public Entity {

public:
  InteractiveEntity(types::layer_t layer, types::point_t position);
  virtual ~InteractiveEntity() = 0;

public:
  virtual bool isWithinSelectionArea(types::coordinate_t posX,
                                     types::coordinate_t posY) const = 0;
  virtual bool isTargetable() const = 0;
  virtual bool isSelectable() const = 0;

public:
  bool isSelected() const;
  void setSelected(bool selected);

private:
  bool selected;
};

} // namespace model
} // namespace how

#endif // INTERACTIVEENTITY_H
