#ifndef CHARACTER_H
#define CHARACTER_H

#include "../graphtypes.h"
#include "./graphentity.h"

namespace how {
namespace model {
class Character : public GraphEntity {

public:
  Character(types::point_t initialPosition);
  ~Character() override;

public:
  types::coordinate_t getWidth() const override;
  types::coordinate_t getHeight() const override;
  bool isTargetable() const override;
  bool isSelectable() const override;
};
} // namespace model
} // namespace how
#endif // CHARACTER_H
