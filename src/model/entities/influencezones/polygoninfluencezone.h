#ifndef BOXINFLUENCEZONE_H
#define BOXINFLUENCEZONE_H

#include "./influencezone.h"

namespace how {
namespace model {
class PolygonInfluenceZone : public InfluenceZone {
public:
  PolygonInfluenceZone(const Entity *parentEntity);
  PolygonInfluenceZone(const types::box_t &envelope,
                       const Entity *parentEntity);
  PolygonInfluenceZone(const types::polygon_t &polygon,
                       const Entity *parentEntity);
  ~PolygonInfluenceZone() override;

public:
  bool isPointWithinZone(const types::point_t &position) const override;
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

#endif // BOXINFLUENCEZONE_H
