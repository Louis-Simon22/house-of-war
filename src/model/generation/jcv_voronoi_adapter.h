#ifndef JCV_VORONOI_ADAPTER_H
#define JCV_VORONOI_ADAPTER_H

#include "../../../lib/voronoi/src/jc_voronoi.h"

#include "../entities/voronoicell.h"
#include "../modeltypes.h"

namespace how {
namespace model {

std::vector<std::shared_ptr<VoronoiCell>>
generateVoronoiCells(types::box_t boundingBox,
                     std::vector<types::point_t> points);

} // namespace model
} // namespace how

#endif // JCV_VORONOI_ADAPTER_H
