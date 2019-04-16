#ifndef JCV_VORONOI_ADAPTER_H
#define JCV_VORONOI_ADAPTER_H

#include "../../../../lib/voronoi/src/jc_voronoi.h"

#include "../../modeltypes.h"
#include "../voronoicell.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

const jcv_rect *convert(types::box_t box);

jcv_point convert(types::point_t point);

const jcv_point *convert(std::vector<types::point_t> points);

std::vector<types::segment_t> extractVoronoiEdges(jcv_diagram *voronoiDiagram);

std::vector<VoronoiCell> extractVoronoiCells(jcv_diagram *voronoiDiagram);

std::pair<std::vector<types::segment_t>, std::vector<VoronoiCell>>
generateVoronoi(types::box_t boundingBox, std::vector<types::point_t> points);
} // namespace model
} // namespace how

#endif // JCV_VORONOI_ADAPTER_H
