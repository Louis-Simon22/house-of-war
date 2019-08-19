#ifndef ZONE_H
#define ZONE_H

#include "./entity.h"

namespace how {
namespace model {
// All coordinates in this class should be absolute
class Zone : public Entity {
public:
  Zone(const Entity *parentEntity);
  virtual ~Zone() = 0;

public:
  virtual bool isPointOverlappingZone(const types::point_t &position) const = 0;
  bool isBoxOverlappingZone(const types::box_t &box) const;
  virtual bool
  isSegmentOverlappingZone(const types::segment_t &segment) const = 0;
  virtual bool
  isPolygonOverlappingZone(const types::polygon_t &polygon) const = 0;
  virtual types::box_t getEnvelope() const = 0;
};
} // namespace model
} // namespace how

#endif // ZONE_H
