#include "boxinfluencezone.h"

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/overlaps.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

BoxInfluenceZone::BoxInfluenceZone(const types::box_t &envelope,
                                   const Entity *parentEntity)
    : InfluenceZone(parentEntity), envelope(envelope), envelopeAsPolygon() {
  bg::convert(envelope, this->envelopeAsPolygon);
}

BoxInfluenceZone::~BoxInfluenceZone() {}

bool BoxInfluenceZone::isPointWithinZone(const types::point_t &position) const {
  return bg::covered_by(position, this->envelope);
}

bool BoxInfluenceZone::isPolygonOverlappingZone(
    types::polygon_t polygon) const {
  return bg::overlaps(polygon, this->envelopeAsPolygon);
}

types::box_t BoxInfluenceZone::getEnvelope() const { return this->envelope; }

} // namespace model
} // namespace how
