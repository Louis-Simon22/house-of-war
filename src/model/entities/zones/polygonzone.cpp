#include "polygonzone.h"

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

PolygonZone::PolygonZone(const Entity *parentEntity)
    : Zone(parentEntity), envelope(), polygon() {}

PolygonZone::PolygonZone(const types::box_t &envelope,
                                           const Entity *parentEntity)
    : PolygonZone(parentEntity) {
  this->setPolygon(envelope);
}

PolygonZone::PolygonZone(const types::polygon_t &polygon,
                                           const Entity *parentEntity)
    : PolygonZone(parentEntity) {
  this->setPolygon(polygon);
}

PolygonZone::~PolygonZone() {}

bool PolygonZone::isPointOverlappingZone(
    const types::point_t &position) const {
  return bg::covered_by(position, this->polygon);
}

bool PolygonZone::isPolygonOverlappingZone(
   const types::polygon_t &polygon) const {
  return bg::overlaps(polygon, this->polygon);
}

bool PolygonZone::isSegmentOverlappingZone(
  const  types::segment_t &segment) const {
  return bg::intersects(segment, this->polygon);
}

types::box_t PolygonZone::getEnvelope() const {
  return this->envelope;
}

void PolygonZone::setPolygon(const types::box_t &envelope) {
  this->envelope = envelope;
  bg::convert(envelope, this->polygon);
}

void PolygonZone::setPolygon(const types::polygon_t &polygon) {
  this->polygon = polygon;
  bg::envelope(polygon, this->envelope);
}

} // namespace model
} // namespace how
