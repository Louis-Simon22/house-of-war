#ifndef ARMY_H
#define ARMY_H

#include "../graphtypes.h"
#include "../modeltypes.h"
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
  bool isWithinSelectionArea(types::coordinate_t posX,
                             types::coordinate_t posY) const override;
  std::shared_ptr<CircularInfluenceZone> getEngagementZonePtr() const;
  std::shared_ptr<CircularInfluenceZone> getForagingZonePtr() const;
  std::shared_ptr<CircularInfluenceZone> getScoutingZonePtr() const;

private:
  std::shared_ptr<CircularInfluenceZone> selectionZonePtr;
  std::shared_ptr<CircularInfluenceZone> engagementZonePtr;
  std::shared_ptr<CircularInfluenceZone> foragingZonePtr;
  std::shared_ptr<CircularInfluenceZone> scoutingZonePtr;
};
} // namespace model
} // namespace how

#endif // ARMY_H
