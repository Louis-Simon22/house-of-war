#ifndef INFLUENCEZONERTREE_H
#define INFLUENCEZONERTREE_H

#include <map>
#include <memory>
#include <vector>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/strategies/strategies.hpp>
#include <boost/iterator/function_output_iterator.hpp>

#include "../entities/zones/zone.h"
#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
namespace bgi = ::boost::geometry::index;
} // namespace
template <typename Value> class InfluenceZoneRTree {
  using index_rtree_value_t = std::pair<types::box_t, const Zone *>;
  using index_rtree_t = bgi::rtree<index_rtree_value_t, bgi::quadratic<16>>;

public:
  InfluenceZoneRTree() : indexRTree() {}

public:
  void addValue(Zone *influenceZone, Value value) {
    this->influenceZoneToValueMap[influenceZone] = value;
    this->indexRTree.insert(
        index_rtree_value_t(influenceZone->getEnvelope(), influenceZone));
  }

  void clearAllValues() {
    this->influenceZoneToValueMap.clear();
    this->indexRTree.clear();
  }

  std::vector<Value> getValuesByPosition(const types::point_t &position) {
    auto coveredValues = std::vector<Value>();

    this->indexRTree.query(
        bgi::covers(position),
        ::boost::make_function_output_iterator(
            [&position, &coveredValues,
             this](const index_rtree_value_t &value) {
              auto *influenceZone = std::get<1>(value);
              if (influenceZone->isPointOverlappingZone(position)) {
                coveredValues.push_back(
                    this->influenceZoneToValueMap[influenceZone]);
              }
            }));

    return coveredValues;
  }

  Value getValueByPosition(const types::point_t &position) {
    auto valuesByPosition = this->getValuesByPosition(position);
    return valuesByPosition.empty() ? Value() : valuesByPosition[0];
  }

  std::vector<Value>
  getValuesBySegmentIntersection(const types::segment_t &segment) {
    auto coveredValues = std::vector<Value>();

    this->indexRTree.query(
        bgi::intersects(segment),
        ::boost::make_function_output_iterator(
            [&coveredValues, &segment, this](const index_rtree_value_t &value) {
              auto *influenceZone = std::get<1>(value);
              if (influenceZone->isSegmentOverlappingZone(segment)) {
                coveredValues.push_back(
                    this->influenceZoneToValueMap[influenceZone]);
              }
            }));

    return coveredValues;
  }

  std::vector<Value> getValuesByBoxIntersection(const types::box_t &box) {
    auto coveredValues = std::vector<Value>();

    this->indexRTree.query(
        bgi::intersects(box),
        ::boost::make_function_output_iterator(
            [&coveredValues, &box, this](const index_rtree_value_t &value) {
              auto *influenceZone = std::get<1>(value);
              if (influenceZone->isBoxOverlappingZone(box)) {
                coveredValues.push_back(
                    this->influenceZoneToValueMap[influenceZone]);
              }
            }));

    return coveredValues;
  }

private:
  index_rtree_t indexRTree;
  std::map<const Zone *, Value> influenceZoneToValueMap;
};
} // namespace model
} // namespace how

#endif // INFLUENCEZONERTREE_H
