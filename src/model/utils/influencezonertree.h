#ifndef SPATIALINDEXLAYER_H
#define SPATIALINDEXLAYER_H

#include <map>
#include <memory>
#include <vector>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "../entities/influencezone.h"
#include "../modeltypes.h"

namespace how {
namespace model {
namespace {
namespace bgi = ::boost::geometry::index;
}
template <typename Value> class InfluenceZoneRTree {
  using index_rtree_value_t =
      std::pair<types::box_t, std::shared_ptr<const InfluenceZone>>;
  using index_rtree_t = bgi::rtree<index_rtree_value_t, bgi::quadratic<16>>;

public:
  InfluenceZoneRTree() : indexRTree() {}

public:
  void addValue(std::shared_ptr<const InfluenceZone> influenceZonePtr,
                Value value) {
    this->influenceZoneToValueMap[influenceZonePtr] = value;
    this->indexRTree.insert(
        index_rtree_value_t(influenceZonePtr->getEnvelope(), influenceZonePtr));
  }

  void removeValue(std::shared_ptr<const InfluenceZone> influenceZonePtr) {
    this->influenceZoneToValueMap.erase(influenceZonePtr);
    this->indexRTree.remove(
        index_rtree_value_t(influenceZonePtr->getEnvelope(), influenceZonePtr));
  }

  std::vector<Value> getValuesByPosition(const types::point_t &position) {
    auto coveredValues = std::vector<Value>();

    this->indexRTree.query(
        bgi::covers(position),
        ::boost::make_function_output_iterator(
            [&position, &coveredValues,
             this](const index_rtree_value_t &value) {
              auto influenceZonePtr = std::get<1>(value);
              if (influenceZonePtr->isPointWithinZone(position)) {
                coveredValues.push_back(
                    this->influenceZoneToValueMap[influenceZonePtr]);
              }
            }));

    return coveredValues;
  }

  //  std::vector<Value>
  //  getValuesByPolygonIntersection(const types::polygon_t &polygon) {
  //    auto coveredValues = std::vector<Value>();

  //    this->indexRTree.query(
  //        bgi::intersects(polygon) &&
  //            bgi::satisfies([&polygon](const index_rtree_value_t &value) {
  //              return value.second->isPolygonOverlappingZone(polygon);
  //            }),
  //        ::boost::make_function_output_iterator(
  //            [&coveredValues, this](
  //                const std::shared_ptr<const InfluenceZone>
  //                &influenceZonePtr) {
  //              coveredValues.push_back(
  //                  this->influenceZoneToValueMap[influenceZonePtr]);
  //            }));

  //    return coveredValues;
  //  }

private:
  index_rtree_t indexRTree;
  std::map<std::shared_ptr<const InfluenceZone>, Value> influenceZoneToValueMap;
};
} // namespace model
} // namespace how

#endif // SPATIALINDEXLAYER_H
