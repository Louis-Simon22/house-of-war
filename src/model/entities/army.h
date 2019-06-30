#ifndef ARMY_H
#define ARMY_H

#include "../graphtypes.h"
#include "./circularinfluencezone.h"
#include "./interactiveentity.h"

namespace how {
namespace model {
class Army : public InteractiveEntity {
public:
  Army(types::point_t initialPosition);
  ~Army() override;

public:
  bool isTargetable() const override;
  bool isSelectable() const override;
  CircularInfluenceZone *getSelectionZone();
  CircularInfluenceZone *getEngagementZone();
  CircularInfluenceZone *getForagingZone();
  CircularInfluenceZone *getScoutingZone();

private:
  CircularInfluenceZone selectionZone;
  CircularInfluenceZone engagementZone;
  CircularInfluenceZone foragingZone;
  CircularInfluenceZone scoutingZone;
};
} // namespace model
} // namespace how

#endif // ARMY_H
