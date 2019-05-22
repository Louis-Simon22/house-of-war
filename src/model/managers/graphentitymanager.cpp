#include "graphentitymanager.h"

#include <set>

#include "../entities/graphentitypositionchange.h"
#include "../operations/pathfindingoperations.h"
#include "../operations/polygonindexoperations.h"
#include "../utils/segmentcomparator.h"

#include <iostream>

namespace how {
namespace model {

GraphEntityManager::GraphEntityManager(types::graph_t graph,
                                       types::box_t bounds)
    : graph(graph), bounds(bounds), spatialIndexTree(), voronoiSegments(),
      delaunaySegments(), graphEntityChangePtrs(), armyPtrs(), characterPtrs(),
      voronoiCellPtrs() {
  types::graph_vertex_iterator_t vertexItBegin, vertexItEnd;
  std::tie(vertexItBegin, vertexItEnd) = ::boost::vertices(graph);
  for (auto vertexIt = vertexItBegin; vertexIt != vertexItEnd; vertexIt++) {
    auto vertexDesc = *vertexIt;
    auto &voronoiCell = *graph[vertexDesc];
    auto &envelope = voronoiCell.getEnvelope();
    this->spatialIndexTree.insert(std::make_pair(envelope, vertexDesc));
  }

  auto uniqueVoronoiSegmentsSet =
      std::set<types::segment_t, SegmentComparator>();
  for (auto vertexIt = vertexItBegin; vertexIt < vertexItEnd; vertexIt++) {
    auto vertexDesc = *vertexIt;
    auto &voronoiCell = *graph[vertexDesc];
    const auto &outlineSegments = voronoiCell.getOutlineSegments();
    for (const auto &outlineSegment : outlineSegments) {
      uniqueVoronoiSegmentsSet.insert(outlineSegment);
    }
  }
  this->voronoiSegments.insert(this->voronoiSegments.end(),
                               uniqueVoronoiSegmentsSet.begin(),
                               uniqueVoronoiSegmentsSet.end());

  types::graph_edge_iterator_t edgeItBegin, edgeItEnd;
  std::tie(edgeItBegin, edgeItEnd) = ::boost::edges(graph);
  auto uniqueDelaunaySegmentsSet =
      std::set<types::segment_t, SegmentComparator>();
  for (auto edgeIt = edgeItBegin; edgeIt != edgeItEnd; edgeIt++) {
    auto edgeDesc = *edgeIt;
    auto &delaunayEdge = *graph[edgeDesc];
    const auto &edgeSegment = delaunayEdge.getSegment();
    uniqueDelaunaySegmentsSet.insert(edgeSegment);
  }
  this->delaunaySegments.insert(this->delaunaySegments.end(),
                                uniqueDelaunaySegmentsSet.begin(),
                                uniqueDelaunaySegmentsSet.end());
}

void GraphEntityManager::addGraphEntityPositionChange(
    GraphEntity *source, GraphEntity *destination) {
  auto destinations = this->getDestinationsBetween(source, destination);
  std::cout << "Destinations : " << destinations.size() << std::endl;
  this->graphEntityChangePtrs.push_back(
      std::make_unique<GraphEntityPositionChange>(source, destinations));
}

void GraphEntityManager::progressAll(float deltaTime) {
  for (auto it = this->graphEntityChangePtrs.begin();
       it != this->graphEntityChangePtrs.end();) {
    if ((*it)->progress(deltaTime)) {
      it = this->graphEntityChangePtrs.erase(it);
    } else {
      it++;
    }
  }
}

void GraphEntityManager::addArmy(std::shared_ptr<Army> armyPtr) {
  this->armyPtrs.push_back(armyPtr);
}

void GraphEntityManager::addCharacter(std::shared_ptr<Character> characterPtr) {
  this->characterPtrs.push_back(characterPtr);
}

void GraphEntityManager::addVoronoiCell(
    std::shared_ptr<VoronoiCell> voronoiCellPtr) {
  this->voronoiCellPtrs.push_back(voronoiCellPtr);
}

const types::graph_t &GraphEntityManager::getGraph() const {
  return this->graph;
}

const types::box_t &GraphEntityManager::getBounds() const {
  return this->bounds;
}

const std::vector<types::segment_t> &
GraphEntityManager::getVoronoiSegments() const {
  return this->voronoiSegments;
}

const std::vector<types::segment_t> &
GraphEntityManager::getDelaunaySegments() const {
  return this->delaunaySegments;
}

std::vector<std::shared_ptr<Army>> &GraphEntityManager::getArmyPtrs() {
  return this->armyPtrs;
}

std::vector<std::shared_ptr<Character>> &
GraphEntityManager::getCharacterPtrs() {
  return this->characterPtrs;
}

std::vector<std::shared_ptr<VoronoiCell>> &
GraphEntityManager::getVoronoiCellPtrs() {
  return this->voronoiCellPtrs;
}

std::shared_ptr<VoronoiCell> GraphEntityManager::getVoronoiCellPtrByDesc(
    types::graph_vertex_desc_t vertexDesc) {
  return this->graph[vertexDesc];
}

types::graph_vertex_desc_t
GraphEntityManager::getVertexDescByPosition(types::point_t position) const {
  return coveredByPoint(position, this->spatialIndexTree, this->graph);
}

VoronoiCell *
GraphEntityManager::getVoronoiCellByPosition(types::point_t position) const {
  return this->graph[this->getVertexDescByPosition(position)].get();
}

std::vector<VoronoiCell *>
GraphEntityManager::getDestinationsBetween(GraphEntity *source,
                                           GraphEntity *destination) {
  const auto sourceVertexDesc =
      this->getVertexDescByPosition(source->getPosition());
  const auto destinationVertexDesc =
      this->getVertexDescByPosition(destination->getPosition());
  return graphEntityPathfinding(sourceVertexDesc, destinationVertexDesc,
                                this->graph);
}

} // namespace model
} // namespace how
