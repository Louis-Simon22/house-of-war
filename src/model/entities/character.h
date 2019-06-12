#ifndef CHARACTER_H
#define CHARACTER_H

#include "../graphtypes.h"
#include "./interactiveentity.h"

namespace how {
namespace model {
class Character : public InteractiveEntity {

public:
  Character(types::point_t initialPosition);
  ~Character() override;

public:
  bool isTargetable() const override;
  bool isSelectable() const override;
};
} // namespace model
} // namespace how
#endif // CHARACTER_H
