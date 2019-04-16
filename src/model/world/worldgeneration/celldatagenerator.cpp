#include "celldatagenerator.h"

#include <math.h>

#include "./elevationgenerator.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;


}

void generateHeightData(types::box_t boundingBox, std::uint32_t randomSeed,
                        types::delaunay_graph_t &graph) {
  const auto &heightMap = generateHeightMap(randomSeed, graph);
  for (std::size_t i = 0; i < ::boost::num_vertices(graph); i++) {
    auto &voronoiCell = graph[i];
    const auto& minCorner = boundingBox.min_corner();
    const auto& maxCorner = boundingBox.max_corner();
    const auto positionRatioY =
        static_cast<double>(bg::get<1>(voronoiCell.centroid)) /
        static_cast<double>(heightMap.size());
    const auto heightMapIndexY =
        static_cast<std::size_t>(floor(positionRatioY * heightMap.size()));
    const auto positionRatioX =
        static_cast<double>(bg::get<0>(voronoiCell.centroid)) /
        static_cast<double>(heightMap[heightMapIndexY].size());
    const auto heightMapIndexX = static_cast<std::size_t>(
        floor(positionRatioX * heightMap[heightMapIndexY].size()));
    const auto &heightValue = heightMap[heightMapIndexY][heightMapIndexX];
    voronoiCell.cellData.elevation = heightValue;
  }
}

} // namespace model
} // namespace how
