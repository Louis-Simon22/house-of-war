#include "delaunayextrapolator.h"

#include "../../../lib/delaunay/include/delaunator.hpp"
#include "../operations/polygonindexoperations.h"

namespace how {
namespace model {

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

void addEdgeToGraph(
    types::graph_t &graph, const types::spatial_index_tree_t &spatialIndexTree,
    std::map<const VoronoiCell *, types::graph_vertex_desc_t> &vertexDescByCell,
    const VoronoiCell *voronoiCellPtr1, const VoronoiCell *voronoiCellPtr2) {
  auto segment = types::segment_t(voronoiCellPtr1->getPosition(),
                                  voronoiCellPtr2->getPosition());
  const auto &bounds = spatialIndexTree.bounds();
  // This removes the edges that go around the edge cells to far away cells
  if (!(isVoronoiCellOnBounds(bounds, voronoiCellPtr1) &&
        isVoronoiCellOnBounds(bounds, voronoiCellPtr2) &&
        intersectingGeometry<>(segment, spatialIndexTree, graph).size() > 2)) {
    auto vertexDesc1 = vertexDescByCell[voronoiCellPtr1];
    auto vertexDesc2 = vertexDescByCell[voronoiCellPtr2];
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
    std::vector<std::shared_ptr<VoronoiCell>> voronoiCells) {
  auto graph = types::graph_t();
  auto vertexDescByCell =
      std::map<const VoronoiCell *, types::graph_vertex_desc_t>();
  auto coords = std::vector<double>();
  for (const auto &voronoiCellPtr : voronoiCells) {
    const auto &position = voronoiCellPtr->getPosition();
    coords.push_back(static_cast<double>(bg::get<0>(position)));
    coords.push_back(static_cast<double>(bg::get<1>(position)));
    auto vertexDesc = ::boost::add_vertex(voronoiCellPtr, graph);
    vertexDescByCell[voronoiCellPtr.get()] = vertexDesc;
  }

  // TODO only do this once
  auto spatialIndexTree = types::spatial_index_tree_t();
  types::graph_vertex_iterator_t vertexItBegin, vertexItEnd;
  std::tie(vertexItBegin, vertexItEnd) = ::boost::vertices(graph);
  for (auto vertexIt = vertexItBegin; vertexIt != vertexItEnd; vertexIt++) {
    auto vertexDesc = *vertexIt;
    auto &voronoiCell = *graph[vertexDesc];
    auto &envelope = voronoiCell.getEnvelope();
    spatialIndexTree.insert(std::make_pair(envelope, vertexDesc));
  }

  auto delaunator = delaunator::Delaunator(coords);
  const auto &triangles = delaunator.triangles;

  for (std::size_t i = 0; i < triangles.size(); i += 3) {
    const auto *voronoiCellPtr1 = voronoiCells[triangles[i]].get();
    const auto *voronoiCellPtr2 = voronoiCells[triangles[i + 1]].get();
    const auto *voronoiCellPtr3 = voronoiCells[triangles[i + 2]].get();
    addEdgeToGraph(graph, spatialIndexTree, vertexDescByCell, voronoiCellPtr1,
                   voronoiCellPtr2);
    addEdgeToGraph(graph, spatialIndexTree, vertexDescByCell, voronoiCellPtr2,
                   voronoiCellPtr3);
    addEdgeToGraph(graph, spatialIndexTree, vertexDescByCell, voronoiCellPtr3,
                   voronoiCellPtr1);
  }

  return graph;
}

} // namespace model
} // namespace how
