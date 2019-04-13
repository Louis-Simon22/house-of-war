#include "worldgenerator.h"

#include <chrono>
#include <iostream>

#include "../../easingfunctions.h"
#include "../../random/poissondisksampling.h"
#include "./celldatagenerator.h"
#include "./delaunayextrapolator.h"

namespace how {
namespace model {

WorldData *generateWorld(const types::WorldGenerationConfig &config) {
  std::cout << "Starting world generation" << std::endl;
  const auto &start = std::chrono::system_clock::now();
  const auto &minCorner = types::point_t(config.minCornerX, config.minCornerY);
  const auto &maxCorner = types::point_t(config.maxCornerX, config.maxCornerY);
  const auto &boundingBox = types::box_t(minCorner, maxCorner);

  const auto &points =
      PoissonDiskSampling<types::point_t>(minCorner, maxCorner, 40, 30)
          .generateSequence();
  std::cout << "Generated points "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
                   .count()
            << std::endl;

  const auto &voronoiPair = buildVoronoi(boundingBox, points);
  const auto &uniqueVoronoiSegments = voronoiPair.first;
  auto voronoiCells = voronoiPair.second;
  std::cout << "Generated voronoi "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
                   .count()
            << std::endl;

  auto delaunayTuple = extrapolateDelaunayTriangulation(voronoiCells);
  auto delaunayGraph = std::get<0>(delaunayTuple);
  auto delaunayEdges = std::get<1>(delaunayTuple);
  const auto &uniqueDelaunaySegments = std::get<2>(delaunayTuple);
  std::cout << "Generated delaunay "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
                   .count()
            << std::endl;

  auto generator = ::boost::random::mt19937();
  const auto &vertexSet = delaunayGraph.vertex_set();
  auto distribution = ::boost::random::uniform_int_distribution<>(
      0, static_cast<int>(vertexSet.size() - 1));
  auto elevationReferenceAccessor =
      [](types::delaunay_graph_vertex_desc_t vertexDesc,
         types::delaunay_graph_t &graph) -> types::characteristics_t & {
    return graph[vertexDesc].cellData.elevation;
  };
  distanceBasedCharacteristicGeneration(
      vertexSet[112], elevationReferenceAccessor, delaunayGraph);
  distanceBasedCharacteristicGeneration(
      vertexSet[114], elevationReferenceAccessor, delaunayGraph);
  normalizeCellCharacteristic(elevationReferenceAccessor, delaunayGraph);
  std::cout << "Generated cell data "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
                   .count()
            << std::endl;

  return new WorldData(boundingBox, uniqueVoronoiSegments,
                       uniqueDelaunaySegments, delaunayGraph);
}
} // namespace model
} // namespace how
