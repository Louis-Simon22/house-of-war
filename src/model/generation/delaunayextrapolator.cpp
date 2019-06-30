#include "delaunayextrapolator.h"

#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/strategies/strategies.hpp>

#include "../../../lib/delaunay/include/delaunator.hpp"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
namespace bgi = ::boost::geometry::index;
using voronoi_cells_rtree_value_t =
    std::pair<types::box_t, std::shared_ptr<const VoronoiCell>>;
using voronoi_cells_rtree_t =
    bgi::rtree<voronoi_cells_rtree_value_t, bgi::quadratic<16>>;
} // namespace

bool isVoronoiCellOnBounds(const types::box_t &bounds,
                           const VoronoiCell *voronoiCellPtr) {
  for (const auto &outlinePoint : voronoiCellPtr->getOutlinePoints()) {
    if (bg::get<0>(outlinePoint) == bg::get<bg::min_corner, 0>(bounds) ||
        bg::get<0>(outlinePoint) == bg::get<bg::max_corner, 0>(bounds) ||
        bg::get<1>(outlinePoint) == bg::get<bg::min_corner, 1>(bounds) ||
        bg::get<1>(outlinePoint) == bg::get<bg::max_corner, 1>(bounds)) {
      return true;
    }
  }
  return false;
}

bool isSegmentIntersectingMoreThanTwoVoronoiCells(
    const types::segment_t &segment,
    const voronoi_cells_rtree_t &voronoiCellsRTree) {
  auto intersecteingValues = std::vector<voronoi_cells_rtree_value_t>();
  voronoiCellsRTree.query(bgi::intersects(segment),
                          std::back_inserter(intersecteingValues));
  return intersecteingValues.size() > 2;
}

void addEdgeToGraph(types::graph_t &graph,
                    const voronoi_cells_rtree_t &voronoiCellsRTree,
                    const VoronoiCell *voronoiCellPtr1,
                    const VoronoiCell *voronoiCellPtr2) {
  auto segment = types::segment_t(voronoiCellPtr1->getPosition(),
                                  voronoiCellPtr2->getPosition());
  const auto &bounds = voronoiCellsRTree.bounds();
  // This doesn't include the edges that wrap around edge cells
  // TODO this removes too many edges
  if (!(isVoronoiCellOnBounds(bounds, voronoiCellPtr1) &&
        isVoronoiCellOnBounds(bounds, voronoiCellPtr2) &&
        isSegmentIntersectingMoreThanTwoVoronoiCells(segment,
                                                     voronoiCellsRTree))) {
    auto vertexDesc1 = voronoiCellPtr1->getVertexDesc();
    auto vertexDesc2 = voronoiCellPtr2->getVertexDesc();
    if (!::boost::edge(vertexDesc1, vertexDesc2, graph).second) {
      auto delaunayEdge1 =
          std::shared_ptr<DelaunayEdge>(new DelaunayEdge(types::segment_t(
              voronoiCellPtr1->getPosition(), voronoiCellPtr2->getPosition())));
      ::boost::add_edge(vertexDesc1, vertexDesc2, delaunayEdge1, graph);
    }
    if (!::boost::edge(vertexDesc2, vertexDesc1, graph).second) {
      auto delaunayEdge2 =
          std::shared_ptr<DelaunayEdge>(new DelaunayEdge(types::segment_t(
              voronoiCellPtr1->getPosition(), voronoiCellPtr2->getPosition())));
      ::boost::add_edge(vertexDesc2, vertexDesc1, delaunayEdge2, graph);
    }
  }
}

types::graph_t createGraphFromVoronoiCellsAndComputeDelaunayTriangulation(
    std::vector<std::shared_ptr<Tile>> tiles) {
  auto graph = types::graph_t();
  auto spatialIndexTree = voronoi_cells_rtree_t();
  auto coords = std::vector<double>();

  for (const auto &voronoiCellPtr : tiles) {
    const auto &position = voronoiCellPtr->getPosition();
    coords.push_back(static_cast<double>(bg::get<0>(position)));
    coords.push_back(static_cast<double>(bg::get<1>(position)));
    auto vertexDesc = ::boost::add_vertex(voronoiCellPtr, graph);
    voronoiCellPtr->setVertexDesc(vertexDesc);
    const auto &envelope =
        voronoiCellPtr->getPolygonInfluenceZone()->getEnvelope();
    spatialIndexTree.insert(std::make_pair<>(envelope, voronoiCellPtr));
  }

  auto delaunator = delaunator::Delaunator(coords);
  const auto &triangles = delaunator.triangles;

  for (std::size_t i = 0; i < triangles.size(); i += 3) {
    const auto *voronoiCellPtr1 = tiles[triangles[i]].get();
    const auto *voronoiCellPtr2 = tiles[triangles[i + 1]].get();
    const auto *voronoiCellPtr3 = tiles[triangles[i + 2]].get();
    addEdgeToGraph(graph, spatialIndexTree, voronoiCellPtr1, voronoiCellPtr2);
    addEdgeToGraph(graph, spatialIndexTree, voronoiCellPtr2, voronoiCellPtr3);
    addEdgeToGraph(graph, spatialIndexTree, voronoiCellPtr3, voronoiCellPtr1);
  }

  return graph;
}

} // namespace model
} // namespace how
