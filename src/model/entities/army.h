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
  bool isTargetable() const override;
  bool isSelectable() const override;
  bool isWithinSelectionArea(types::coordinate_t posX,
                          types::coordinate_t posY) const override;
  types::coordinate_t getDetectionRadius() const;

public:
  void onIteration(float deltaTime);

private:
  types::coordinate_t influenceAreaWidth = 50;
};
} // namespace model
} // namespace how

#endif // ARMY_H
