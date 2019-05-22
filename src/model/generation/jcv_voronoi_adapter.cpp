#define JC_VORONOI_IMPLEMENTATION
#include "./jcv_voronoi_adapter.h"

#include <set>

#include "../utils/clockwisepointcomparator.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
} // namespace

const jcv_rect *convert(types::box_t box) {
  auto *jcvRect = new jcv_rect();
  auto jcvMinCorner = jcv_point();
  auto jcvMaxCorner = jcv_point();
  jcvMinCorner.x = bg::get<bg::min_corner, 0>(box);
  jcvMinCorner.y = bg::get<bg::min_corner, 1>(box);
  jcvMaxCorner.x = bg::get<bg::max_corner, 0>(box);
  jcvMaxCorner.y = bg::get<bg::max_corner, 1>(box);
  jcvRect->min = jcvMinCorner;
  jcvRect->max = jcvMaxCorner;
  return jcvRect;
}

jcv_point convert(types::point_t point) {
  auto jcvRect = jcv_point();
  jcvRect.x = static_cast<types::coordinate_t>(bg::get<0>(point));
  jcvRect.y = static_cast<types::coordinate_t>(bg::get<1>(point));
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

std::vector<std::shared_ptr<VoronoiCell>>
extractVoronoiCells(jcv_diagram *voronoiDiagram) {
  auto voronoiCells = std::vector<std::shared_ptr<VoronoiCell>>();
  const jcv_site *sites = jcv_diagram_get_sites(voronoiDiagram);
  for (int i = 0; i < voronoiDiagram->numsites; ++i) {
    const jcv_site *site = &sites[i];
    const auto center = convert(site->p);
    const jcv_graphedge *edge = site->edges;
    auto cellOutlinePointsSet =
        std::set<types::point_t, ClockwisePointComparator>(center);
    while (edge) {
      if (!jcv_point_eq(&edge->pos[0], &edge->pos[1])) {
        cellOutlinePointsSet.insert(convert(edge->pos[0]));
      }
      edge = edge->next;
    }
    voronoiCells.push_back(std::shared_ptr<VoronoiCell>(new VoronoiCell(
        center, std::vector<types::point_t>(cellOutlinePointsSet.begin(),
                                            cellOutlinePointsSet.end()))));
  }
  return voronoiCells;
}

std::vector<std::shared_ptr<VoronoiCell>>
generateVoronoiCells(types::box_t boundingBox,
                     std::vector<types::point_t> points) {
  auto diagram = jcv_diagram();
  memset(&diagram, 0, sizeof(jcv_diagram));
  const jcv_point *jcvPoints = convert(points);
  const jcv_rect *jcvBoundingBox = convert(boundingBox);

  jcv_diagram_generate(static_cast<int>(points.size()), jcvPoints,
                       jcvBoundingBox, &diagram);

  auto voronoiCells = extractVoronoiCells(&diagram);

  jcv_diagram_free(&diagram);
  delete jcvBoundingBox;
  delete[] jcvPoints;

  return voronoiCells;
}
} // namespace model
} // namespace how
