#ifndef WORLDDATA_H
#define WORLDDATA_H

#include <memory>
#include <vector>

#include "../delaunaygraphtypes.h"
#include "../modeltypes.h"
#include "./voronoicell.h"

namespace how {
namespace model {

class WorldData {
public:
  WorldData(types::box_t bounds, std::vector<types::point_t> points,
            std::vector<types::segment_t> outlineSegments,
            std::vector<types::segment_t> pathSegments,
            std::vector<VoronoiCell> voronoiCells,
            std::vector<DelaunayEdge> delaunayEdges,
            types::delaunay_graph_t graph);

  const types::box_t *getBounds() const;
  const std::vector<types::point_t> *getCellCentroids() const;
  const std::vector<types::segment_t> *getUniqueVoronoiSegments() const;
  const std::vector<types::segment_t> *getUniqueDelaunaySegments() const;
  const std::vector<VoronoiCell> *getVoronoiCells() const;
  const std::vector<DelaunayEdge> *getDelaunayEdges() const;
  const types::delaunay_graph_t *getGraph() const;

private:
  types::box_t bounds;
  std::vector<types::point_t> cellCentroids;
  std::vector<types::segment_t> uniqueVoronoiSegments;
  std::vector<types::segment_t> uniqueDelaunaySegments;
  std::vector<VoronoiCell> voronoiCells;
  std::vector<DelaunayEdge> delaunayEdges;
  types::delaunay_graph_t graph;
};
} // namespace model
} // namespace how
#endif // WORLDDATA_H
