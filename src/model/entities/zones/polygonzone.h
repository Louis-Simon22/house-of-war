#ifndef POLYGONZONE_H
#define POLYGONZONE_H

#include "./zone.h"

namespace how {
namespace model {
class PolygonZone : public Zone {
public:
  PolygonZone(const Entity *parentEntity);
  PolygonZone(const types::box_t &envelope,
                       const Entity *parentEntity);
  PolygonZone(const types::polygon_t &polygon,
                       const Entity *parentEntity);
  ~PolygonZone() override;

public:
  bool isPointOverlappingZone(const types::point_t &position) const override;
  bool isPolygonOverlappingZone(const types::polygon_t &polygon) const override;
  bool isSegmentOverlappingZone(const types::segment_t &segment) const override;
  types::box_t getEnvelope() const override;

public:
  void setPolygon(const types::box_t &envelope);
  void setPolygon(const types::polygon_t &polygon);

private:
  types::box_t envelope;
  types::polygon_t polygon;
};
} // namespace model
} // namespace how

#endif // POLYGONZONE_H
