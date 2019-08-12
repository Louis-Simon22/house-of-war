#include "delaunayextrapolator.h"

#include <algorithm>

#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/strategies/strategies.hpp>

#include "../../../lib/delaunay/include/delaunator.hpp"
#include "../utils/influencezonertree.h"
#include "../utils/pointcomparator.h"
#include "../utils/segmentcomparator.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
namespace bgi = ::boost::geometry::index;
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

// An edge is invalid if the segment joining them overlaps more than two edge
// cells
bool isEdgeValid(
    const types::box_t &bounds,
    InfluenceZoneRTree<std::shared_ptr<VoronoiCell>> &voronoiCellsRTree,
    const VoronoiCell *voronoiCellPtr1, const VoronoiCell *voronoiCellPtr2) {
  if (!isVoronoiCellOnBounds(bounds, voronoiCellPtr1) ||
      !isVoronoiCellOnBounds(bounds, voronoiCellPtr2)) {
    return true;
  }
  auto segment = types::segment_t(voronoiCellPtr1->getPosition(),
                                  voronoiCellPtr2->getPosition());
  auto intersectingCellPtrs =
      voronoiCellsRTree.getValuesBySegmentIntersection(segment);
  int intersectingEdgeCells = 0;
  for (auto &intersectingCellPtr : intersectingCellPtrs) {
    if (isVoronoiCellOnBounds(bounds, intersectingCellPtr.get())) {
      intersectingEdgeCells++;
    }
  }
  return intersectingEdgeCells <= 2;
}

void addEdgeToGraph(
    types::graph_t &graph, const types::box_t &bounds,
    InfluenceZoneRTree<std::shared_ptr<VoronoiCell>> &voronoiCellsRTree,
    const VoronoiCell *voronoiCellPtr1, const VoronoiCell *voronoiCellPtr2) {
  // This doesn't include the edges that wrap around edge cells
  if (isEdgeValid(bounds, voronoiCellsRTree, voronoiCellPtr1,
                  voronoiCellPtr2)) {
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
    std::vector<std::shared_ptr<Tile>> &tiles, const types::box_t &bounds) {
  auto graph = types::graph_t();
  auto spatialIndexTree = InfluenceZoneRTree<std::shared_ptr<VoronoiCell>>();
  auto coords = std::vector<double>();

  for (const auto &tilePtr : tiles) {
    const auto &position = tilePtr->getPosition();
    coords.push_back(static_cast<double>(bg::get<0>(position)));
    coords.push_back(static_cast<double>(bg::get<1>(position)));
    auto vertexDesc = ::boost::add_vertex(tilePtr, graph);
    tilePtr->setVertexDesc(vertexDesc);
    spatialIndexTree.addValue(tilePtr->getPolygonInfluenceZone(), tilePtr);
  }

  auto delaunator = delaunator::Delaunator(coords);
  const auto &triangles = delaunator.triangles;

  for (std::size_t i = 0; i < triangles.size(); i += 3) {
    const auto *voronoiCellPtr1 = tiles[triangles[i]].get();
    const auto *voronoiCellPtr2 = tiles[triangles[i + 1]].get();
    const auto *voronoiCellPtr3 = tiles[triangles[i + 2]].get();
    addEdgeToGraph(graph, bounds, spatialIndexTree, voronoiCellPtr1,
                   voronoiCellPtr2);
    addEdgeToGraph(graph, bounds, spatialIndexTree, voronoiCellPtr2,
                   voronoiCellPtr3);
    addEdgeToGraph(graph, bounds, spatialIndexTree, voronoiCellPtr3,
                   voronoiCellPtr1);
  }

  return graph;
}

} // namespace model
} // namespace how
