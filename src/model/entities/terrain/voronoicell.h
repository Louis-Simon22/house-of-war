#ifndef VORONOICELL_H
#define VORONOICELL_H

#include <vector>

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
              std::vector<types::point_t> outlinePoints);
  virtual ~VoronoiCell() = 0;

public:
  std::size_t getVertexDesc() const;
  void setVertexDesc(std::size_t vertexDesc);
  const types::polygon_t &getPolygon() const;
  const std::vector<types::point_t> &getOutlinePoints() const;
  const std::vector<types::point_t> &getRelativeOutlinePoints() const;
  const std::vector<types::segment_t> &getOutlineSegments() const;
  PolygonInfluenceZone *getPolygonInfluenceZone();

private:
  std::size_t vertexDesc;
  std::vector<types::point_t> outlinePoints;
  std::vector<types::point_t> relativeOutlinePoints;
  types::polygon_t polygon;
  PolygonInfluenceZone polygonInfluenceZone;
  std::vector<types::segment_t> outlineSegments;
};

} // namespace model
} // namespace how

#endif // VORONOICELL_H
