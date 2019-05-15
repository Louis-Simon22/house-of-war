#ifndef ARMY_H
#define ARMY_H

#include "../graphtypes.h"
#include "../modeltypes.h"
#include "./graphentity.h"

namespace how {
namespace model {
class Army : public GraphEntity {
public:
  Army(types::point_t initialPosition);
  ~Army() override;

public:
  types::coordinate_t getWidth() const override;
  types::coordinate_t getHeight() const override;
  bool isTargetable() const override;
  bool isSelectable() const override;

public:
  void onIteration(float deltaTime);

private:
  types::coordinate_t influenceAreaWidth = 50;
};
} // namespace model
} // namespace how

#endif // ARMY_H
