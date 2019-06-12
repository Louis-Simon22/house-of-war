#ifndef BOXINFLUENCEZONE_H
#define BOXINFLUENCEZONE_H

#include "./influencezone.h"

namespace how {
namespace model {
class BoxInfluenceZone : public InfluenceZone {
public:
  BoxInfluenceZone(const types::box_t &envelope, const Entity *parentEntity);
  ~BoxInfluenceZone() override;

public:
  bool isPointWithinZone(const types::point_t &position) const override;
  bool isPolygonOverlappingZone(types::polygon_t polygon) const override;
  types::box_t getEnvelope() const override;

private:
  types::box_t envelope;
  types::polygon_t envelopeAsPolygon;
};
} // namespace model
} // namespace how

#endif // BOXINFLUENCEZONE_H
