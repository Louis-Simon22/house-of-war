#ifndef INFLUENCEZONERTREE_H
#define INFLUENCEZONERTREE_H

#include <map>
#include <memory>
#include <vector>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/strategies/strategies.hpp>

#include "../entities/influencezone.h"
#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace bgi = ::boost::geometry::index;
}
template <typename Value> class InfluenceZoneRTree {
  using index_rtree_value_t = std::pair<types::box_t, const InfluenceZone *>;
  using index_rtree_t = bgi::rtree<index_rtree_value_t, bgi::quadratic<16>>;

public:
  InfluenceZoneRTree() : indexRTree() {}

public:
  void addValue(InfluenceZone *influenceZone, Value value) {
    this->influenceZoneToValueMap[influenceZone] = value;
    this->indexRTree.insert(
        index_rtree_value_t(influenceZone->getEnvelope(), influenceZone));
  }

  void removeValue(const InfluenceZone *influenceZone) {
    this->influenceZoneToValueMap.erase(influenceZone);
    this->indexRTree.remove(
        index_rtree_value_t(influenceZone->getEnvelope(), influenceZone));
  }

  std::vector<Value> getValuesByPosition(const types::point_t &position) {
    auto coveredValues = std::vector<Value>();

    this->indexRTree.query(
        bgi::covers(position),
        ::boost::make_function_output_iterator(
            [&position, &coveredValues,
             this](const index_rtree_value_t &value) {
              auto *influenceZone = std::get<1>(value);
              if (influenceZone->isPointWithinZone(position)) {
                coveredValues.push_back(
                    this->influenceZoneToValueMap[influenceZone]);
              }
            }));

    return coveredValues;
  }

  std::vector<Value>
  getValuesByEnvelopeIntersection(const types::box_t &envelope) {
    auto coveredValues = std::vector<Value>();

    this->indexRTree.query(
        bgi::intersects(envelope),
        ::boost::make_function_output_iterator(
            [&coveredValues, this](const index_rtree_value_t &value) {
              auto *influenceZone = std::get<1>(value);
              coveredValues.push_back(
                  this->influenceZoneToValueMap[influenceZone]);
            }));

    return coveredValues;
  }

  std::vector<Value>
  getValuesByPolygonIntersection(const types::polygon_t &polygon) {
    auto coveredValues = std::vector<Value>();

    this->indexRTree.query(
        bgi::intersects(polygon),
        ::boost::make_function_output_iterator(
            [&coveredValues, &polygon, this](const index_rtree_value_t &value) {
              auto *influenceZone = std::get<1>(value);
              if (influenceZone->isPolygonOverlappingZone(polygon)) {
                coveredValues.push_back(
                    this->influenceZoneToValueMap[influenceZone]);
              }
            }));

    return coveredValues;
  }

private:
  index_rtree_t indexRTree;
  std::map<const InfluenceZone *, Value> influenceZoneToValueMap;
};
} // namespace model
} // namespace how

#endif // INFLUENCEZONERTREE_H
