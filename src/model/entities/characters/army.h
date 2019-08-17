#ifndef ARMY_H
#define ARMY_H

#include "./circularzone.h"
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
  CircularZone *getSelectionZone();
  CircularZone *getEngagementZone();
  CircularZone *getForagingZone();
  CircularZone *getScoutingZone();

private:
  CircularZone selectionZone;
  CircularZone engagementZone;
  CircularZone foragingZone;
  CircularZone scoutingZone;
};
} // namespace model
} // namespace how

#endif // ARMY_H
