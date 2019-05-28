#ifndef ARMY_H
#define ARMY_H

#include "../graphtypes.h"
#include "../modeltypes.h"
#include "./circularinfluencezone.h"
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
  const CircularInfluenceZone &getSelectionZone();
  const CircularInfluenceZone &getEngagementZone();
  const CircularInfluenceZone &getForagingZone();
  const CircularInfluenceZone &getScoutingZone();

private:
  CircularInfluenceZone selectionZone;
  CircularInfluenceZone engagementZone;
  CircularInfluenceZone foragingZone;
  CircularInfluenceZone scoutingZone;
};
} // namespace model
} // namespace how

#endif // ARMY_H
