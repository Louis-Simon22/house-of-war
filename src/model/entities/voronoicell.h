#ifndef VORONOICELL_H
#define VORONOICELL_H

#include <vector>

#include "../graphtypes.h"
#include "./interactiveentity.h"
#include "./polygoninfluencezone.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
} // namespace

class VoronoiCell : public InteractiveEntity {
public:
  VoronoiCell(types::point_t position,
              std::vector<types::point_t> relativeOutlinePoints);
  virtual ~VoronoiCell() = 0;

public:
  types::graph_vertex_desc_t getVertexDesc() const;
  const types::polygon_t &getPolygon() const;
  const std::vector<types::point_t> &getOutlinePoints() const;
  const std::vector<types::point_t> &getRelativeOutlinePoints() const;
  const std::vector<types::segment_t> &getOutlineSegments() const;
  PolygonInfluenceZone *getPolygonInfluenceZone();

public:
  void setVertexDesc(types::graph_vertex_desc_t vertexDesc);

private:
  types::graph_vertex_desc_t vertexDesc;
  std::vector<types::point_t> outlinePoints;
  std::vector<types::point_t> relativeOutlinePoints;
  types::polygon_t polygon;
  PolygonInfluenceZone polygonInfluenceZone;
  std::vector<types::segment_t> outlineSegments;
};

} // namespace model
} // namespace how

#include "./tile.h"

#endif // VORONOICELL_H
