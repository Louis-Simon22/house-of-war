#ifndef INFLUENCEZONE_H
#define INFLUENCEZONE_H

#include "../modeltypes.h"
#include "./graphentity.h"

namespace how {
namespace model {
class InfluenceZone {
public:
  InfluenceZone(const GraphEntity &attachedEntity);
  virtual ~InfluenceZone() = 0;

public:
  virtual bool isPointWithinZone(types::coordinate_t posX,
                                 types::coordinate_t posY) const = 0;
  virtual bool isPolygonOverlappingZone(types::polygon_t polygon) const = 0;
  virtual types::box_t getEnvelope() const = 0;

protected:
  const GraphEntity &attachedEntity;
};
} // namespace model
} // namespace how

#endif // INFLUENCEZONE_H
