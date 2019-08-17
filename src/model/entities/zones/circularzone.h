#ifndef CIRCULARZONE_H
#define CIRCULARZONE_H

#include "./zone.h"

namespace how {
namespace model {
class CircularZone : public Zone {
public:
  CircularZone(types::coordinate_t radius, const Entity *parentEntity);
  ~CircularZone() override;

public:
  bool isPointOverlappingZone(const types::point_t &position) const override;
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

#endif // CIRCULARZONE_H
