#include "celldatagenerator.h"

#include <math.h>

#include <boost/geometry/arithmetic/arithmetic.hpp>

#include "../operations/celldataoperations.h"
#include "./elevationgenerator.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

void generateHeightData(types::box_t boundingBox, std::uint32_t randomSeed,
                        types::graph_t &graph) {
  const auto *noiseModule = generateHeightMap(randomSeed);
  const auto minCorner = boundingBox.min_corner();
  const auto maxCorner = boundingBox.max_corner();
  auto dimensions = maxCorner;
  bg::subtract_point(dimensions, minCorner);
  for (std::size_t i = 0; i < ::boost::num_vertices(graph); i++) {
    auto &voronoiCellPtr = graph[i];
    auto positionRatios = voronoiCellPtr->getPosition();
    bg::subtract_point(positionRatios, minCorner);
    bg::divide_point(positionRatios, dimensions);
    auto nx = static_cast<double>(bg::get<0>(positionRatios));
    auto ny = static_cast<double>(bg::get<1>(positionRatios));
    const auto heightValue = noiseModule->GetValue(nx, ny, 0);
    voronoiCellPtr->getTile().setAltitude(static_cast<float>(heightValue));
  }

  auto heightReferenceAccessor =
      [](types::graph_vertex_desc_t desc,
         types::graph_t &graph) -> types::charac_t & {
    return graph[desc]->getTile().getAltitude();
  };
  normalizeCellCharacteristic01(heightReferenceAccessor, graph);
}

} // namespace model
} // namespace how
