#include "polygoninfluencezone.h"

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/overlaps.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/strategies/strategies.hpp>

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

PolygonInfluenceZone::PolygonInfluenceZone(const Entity *parentEntity)
    : InfluenceZone(parentEntity), envelope(), polygon() {}

PolygonInfluenceZone::PolygonInfluenceZone(const types::box_t &envelope,
                                           const Entity *parentEntity)
    : PolygonInfluenceZone(parentEntity) {
  this->setPolygon(envelope);
}

PolygonInfluenceZone::PolygonInfluenceZone(const types::polygon_t &polygon,
                                           const Entity *parentEntity)
    : PolygonInfluenceZone(parentEntity) {
  this->setPolygon(polygon);
}

PolygonInfluenceZone::~PolygonInfluenceZone() {}

bool PolygonInfluenceZone::isPointWithinZone(
    const types::point_t &position) const {
  return bg::covered_by(position, this->polygon);
}

bool PolygonInfluenceZone::isPolygonOverlappingZone(
   const types::polygon_t &polygon) const {
  return bg::overlaps(polygon, this->polygon);
}

bool PolygonInfluenceZone::isSegmentOverlappingZone(
  const  types::segment_t &segment) const {
  return bg::intersects(segment, this->polygon);
}

types::box_t PolygonInfluenceZone::getEnvelope() const {
  return this->envelope;
}

void PolygonInfluenceZone::setPolygon(const types::box_t &envelope) {
  this->envelope = envelope;
  bg::convert(envelope, this->polygon);
}

void PolygonInfluenceZone::setPolygon(const types::polygon_t &polygon) {
  this->polygon = polygon;
  bg::envelope(polygon, this->envelope);
}

} // namespace model
} // namespace how
