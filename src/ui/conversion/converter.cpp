#include "converter.h"

#include <QPoint>
#include <boost/geometry/algorithms/for_each.hpp>
#include <set>

#include "../../model/modeltypes.h"
#include "../../model/pointcomparator.h"

namespace how {
namespace ui {

QVariantList convert(const std::vector<model::types::segment_t> *segments) {
  auto pointsSet = std::set<model::types::point_t, model::PointComparator>();
  auto segmentList = QVariantList();

  for (auto segment : *segments) {
    auto convertedSegment = QVariantList();
    convertedSegment.insert(convertedSegment.size(), convert(segment.first));
    convertedSegment.insert(convertedSegment.size(), convert(segment.second));
    segmentList.insert(segmentList.size(), convertedSegment);
  }

  return segmentList;
}

QVariantList convert(const std::vector<model::types::point_t> *points) {
  auto pointList = QVariantList();

  for (auto point : *points) {
    pointList.insert(pointList.size(), convert(point));
  }

  return pointList;
}

QPoint convert(const model::types::point_t point) {
  return QPoint(bg::get<0>(point), bg::get<1>(point));
}

QRect convert(const model::types::box_t *box) {
  return QRect(
      bg::get<bg::min_corner, 0>(box), bg::get<bg::min_corner, 1>(box),
      bg::get<bg::max_corner, 0>(box) - bg::get<bg::min_corner, 0>(box),
      bg::get<bg::max_corner, 1>(box) - bg::get<bg::min_corner, 1>(box));
}

namespace {
class PolygonPointsConverter {
public:
  PolygonPointsConverter(QPolygon polygon) : polygon(polygon) {}

private:
  QPolygon polygon;

public:
  void operator()(::how::model::types::point_t point) { polygon << convert(point); }
};
} // namespace

QPolygon convert(const model::types::polygon_t *polygon) {
  auto convertedPolygon = QPolygon();

  bg::for_each_point(*polygon, PolygonPointsConverter(convertedPolygon));

  return convertedPolygon;
}

} // namespace ui
} // namespace how
