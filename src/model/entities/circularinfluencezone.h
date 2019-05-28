#ifndef CIRCULARINFLUENCEZONE_H
#define CIRCULARINFLUENCEZONE_H

#include "./influencezone.h"

namespace how {
namespace model {
class CircularInfluenceZone : public InfluenceZone {
public:
  CircularInfluenceZone(types::coordinate_t radius,
                        const GraphEntity &attachedGraphEntity);
  ~CircularInfluenceZone() override;

public:
  bool isPointWithinZone(types::coordinate_t posX,
                         types::coordinate_t posY) const override;
  bool isPolygonOverlappingZone(types::polygon_t polygon) const override;
  types::box_t getEnvelope() const override;

public:
  types::coordinate_t getRadius() const;
  void setRadius(types::coordinate_t radius);

private:
  types::coordinate_t radius;
};
} // namespace model
} // namespace how

#endif // CIRCULARINFLUENCEZONE_H
