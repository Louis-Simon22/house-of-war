#ifndef VORONOICELL_H
#define VORONOICELL_H

#include <vector>

#include "./interactiveentity.h"
#include "./polygonzone.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
using vertex_desc_t = unsigned long;
} // namespace
class VoronoiCell : public InteractiveEntity {
public:
  VoronoiCell(types::point_t position,
              std::vector<types::point_t> outlinePoints);
  virtual ~VoronoiCell() = 0;

public:
  vertex_desc_t getVertexDesc() const;
  void setVertexDesc(vertex_desc_t vertexDesc);
  const types::polygon_t &getPolygon() const;
  const std::vector<types::point_t> &getOutlinePoints() const;
  const std::vector<types::point_t> &getRelativeOutlinePoints() const;
  const std::vector<types::segment_t> &getOutlineSegments() const;
  PolygonZone *getPolygonInfluenceZone();

private:
  vertex_desc_t vertexDesc;
  std::vector<types::point_t> outlinePoints;
  std::vector<types::point_t> relativeOutlinePoints;
  types::polygon_t polygon;
  PolygonZone polygonInfluenceZone;
  std::vector<types::segment_t> outlineSegments;
};

} // namespace model
} // namespace how

#endif // VORONOICELL_H
