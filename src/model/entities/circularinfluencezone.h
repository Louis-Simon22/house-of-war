#ifndef CIRCULARINFLUENCEZONE_H
#define CIRCULARINFLUENCEZONE_H

#include "./influencezone.h"

namespace how {
namespace model {
class CircularInfluenceZone : public InfluenceZone {
public:
  CircularInfluenceZone(types::coordinate_t radius, const Entity *parentEntity);
  ~CircularInfluenceZone() override;

public:
  bool isPointWithinZone(const types::point_t &position) const override;
  bool isPolygonOverlappingZone(const types::polygon_t &polygon) const override;
  bool isSegmentOverlappingZone(const types::segment_t &segment) const override;
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
