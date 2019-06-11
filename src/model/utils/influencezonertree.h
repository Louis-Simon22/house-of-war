#ifndef SPATIALINDEXLAYER_H
#define SPATIALINDEXLAYER_H

#include <map>
#include <vector>

#include <boost/geometry/index/rtree.hpp>

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
  void addValue(const InfluenceZone *influenceZone, Value value) {
    this->influenceZoneToValueMap[influenceZone] = value;
    this->indexRTree.insert(
        index_rtree_value_t(influenceZone->getEnvelope(), influenceZone));
  }

  std::vector<Value> getValuesByPosition(const types::point_t &position) const {
    auto coveredValues = std::vector<Value>();

    this->indexRTree.query(
        bgi::intersects(position) &&
            bgi::satisfies([&position](const InfluenceZone *&influenceZone) {
              return influenceZone->isPointWithinZone(position);
            }),
        ::boost::make_function_output_iterator(
            [&coveredValues, this](const InfluenceZone *&influenceZone) {
              coveredValues.push_back(
                  this->influenceZoneToValueMap[influenceZone]);
            }));

    return coveredValues;
  }

  std::vector<Value>
  getVertexDescByPolygon(const types::polygon_t &polygon) const {
    auto coveredValues = std::vector<Value>();

    this->indexRTree.query(
        bgi::intersects(polygon) &&
            bgi::satisfies([&polygon](const InfluenceZone *&influenceZone) {
              return influenceZone->isPolygonOverlappingZone(polygon);
            }),
        ::boost::make_function_output_iterator(
            [&coveredValues, this](const InfluenceZone *&influenceZone) {
              coveredValues.push_back(
                  this->influenceZoneToValueMap[influenceZone]);
            }));

    return coveredValues;
  }

private:
  index_rtree_t indexRTree;
  std::map<const InfluenceZone *, Value> influenceZoneToValueMap;
};
} // namespace model
} // namespace how

#endif // SPATIALINDEXLAYER_H
