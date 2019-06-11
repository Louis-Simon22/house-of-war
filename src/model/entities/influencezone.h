#ifndef INFLUENCEZONE_H
#define INFLUENCEZONE_H

#include "./entity.h"

namespace how {
namespace model {
// All coordinates in this class should be absolute
class InfluenceZone : public Entity {
public:
  InfluenceZone(const Entity *parentEntity);
  virtual ~InfluenceZone() = 0;

public:
  virtual bool isPointWithinZone(const types::point_t &position) const = 0;
  virtual bool isPolygonOverlappingZone(types::polygon_t polygon) const = 0;
  virtual types::box_t getEnvelope() const = 0;
};
} // namespace model
} // namespace how

#endif // INFLUENCEZONE_H
