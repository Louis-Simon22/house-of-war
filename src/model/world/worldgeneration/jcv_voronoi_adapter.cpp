#define JC_VORONOI_IMPLEMENTATION
#include "./jcv_voronoi_adapter.h"

#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <set>

#include "../../clockwisepointcomparator.h"
//#include "../../pointcomparator.h"
#include "../../segmentcomparator.h"

namespace how {
namespace model {

const jcv_rect *convert(types::box_t box) {
  auto jcvRect = new jcv_rect();
  auto jcvMinCorner = jcv_point();
  auto jcvMaxCorner = jcv_point();
  jcvMinCorner.x =
      static_cast<types::coordinate_fpt_t>(bg::get<bg::min_corner, 0>(box));
  jcvMinCorner.y =
      static_cast<types::coordinate_fpt_t>(bg::get<bg::min_corner, 1>(box));
  jcvMaxCorner.x =
      static_cast<types::coordinate_fpt_t>(bg::get<bg::max_corner, 0>(box));
  jcvMaxCorner.y =
      static_cast<types::coordinate_fpt_t>(bg::get<bg::max_corner, 1>(box));
  jcvRect->min = jcvMinCorner;
  jcvRect->max = jcvMaxCorner;
  return jcvRect;
}

jcv_point convert(types::point_t point) {
  auto jcvRect = jcv_point();
  jcvRect.x = static_cast<types::coordinate_fpt_t>(bg::get<0>(point));
  jcvRect.y = static_cast<types::coordinate_fpt_t>(bg::get<1>(point));
  return jcvRect;
}

types::point_t convert(jcv_point point) {
  return types::point_t(static_cast<types::coordinate_t>(point.x),
                        static_cast<types::coordinate_t>(point.y));
}

const jcv_point *convert(std::vector<types::point_t> points) {
  jcv_point *jcvPoint = new jcv_point[points.size()];
  for (std::size_t i = 0; i < points.size(); i++) {
    jcvPoint[i] = convert(points[i]);
  }
  return jcvPoint;
}

std::vector<types::segment_t>
extractVoronoiEdges(std::vector<VoronoiCell> voronoiCells) {
  auto voronoiEdgesSet = std::set<types::segment_t, SegmentComparator>();
  for (const auto &voronoiCell : voronoiCells) {
    voronoiEdgesSet.insert(voronoiCell.outlineSegments.begin(),
                           voronoiCell.outlineSegments.end());
  }
  return std::vector<types::segment_t>(voronoiEdgesSet.begin(),
                                       voronoiEdgesSet.end());
}

std::vector<VoronoiCell> extractVoronoiCells(jcv_diagram *voronoiDiagram) {
  auto voronoiCells = std::vector<VoronoiCell>();
  const jcv_site *sites = jcv_diagram_get_sites(voronoiDiagram);
  for (int i = 0; i < voronoiDiagram->numsites; ++i) {
    const jcv_site *site = &sites[i];
    const auto &center = convert(site->p);
    const jcv_graphedge *edge = site->edges;
    auto cellOutlinePointsSet =
        std::set<types::point_t, ClockwisePointComparator>(center);
    auto cellEdgesSet = std::set<types::segment_t, SegmentComparator>();
    while (edge) {
      if (!jcv_point_eq(&edge->pos[0], &edge->pos[1])) {
        cellOutlinePointsSet.insert(convert(edge->pos[0]));
        cellOutlinePointsSet.insert(convert(edge->pos[1]));
        const auto &segment =
            types::segment_t(convert(edge->pos[0]), convert(edge->pos[1]));
        cellEdgesSet.insert(segment);
      }
      edge = edge->next;
    }
    auto polygon = types::polygon_t();
    for (const auto &point : cellOutlinePointsSet) {
      bg::append(polygon.outer(), point);
    }
    // Add the first point again to close the polygon
    bg::append(polygon.outer(), *cellOutlinePointsSet.begin());
    auto envelopeBox = types::box_t();
    bg::envelope(polygon, envelopeBox);
    voronoiCells.push_back(
        VoronoiCell(envelopeBox, center, polygon,
                    std::vector<types::point_t>(cellOutlinePointsSet.begin(),
                                                cellOutlinePointsSet.end()),
                    std::vector<types::segment_t>(cellEdgesSet.begin(),
                                                  cellEdgesSet.end())));
  }
  return voronoiCells;
}

std::pair<std::vector<types::segment_t>, std::vector<VoronoiCell>>
buildVoronoi(types::box_t boundingBox, std::vector<types::point_t> points) {
  auto diagram = jcv_diagram();
  memset(&diagram, 0, sizeof(jcv_diagram));
  const jcv_point *jcvPoints = convert(points);
  const jcv_rect *jcvBoundingBox = convert(boundingBox);

  jcv_diagram_generate(static_cast<int>(points.size()), jcvPoints,
                       jcvBoundingBox, &diagram);

  auto voronoiCells = extractVoronoiCells(&diagram);
  auto voronoiEdges = extractVoronoiEdges(voronoiCells);

  jcv_diagram_free(&diagram);
  delete jcvBoundingBox;
  delete[] jcvPoints;

  return std::make_pair(voronoiEdges, voronoiCells);
}
} // namespace model
} // namespace how
