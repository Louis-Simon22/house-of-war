#ifndef VORONOICELL_H
#define VORONOICELL_H

#include <vector>

#include "../graphtypes.h"
#include "./interactiveentity.h"
#include "./tile.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
} // namespace

class VoronoiCell : public InteractiveEntity {
public:
  VoronoiCell(types::point_t position,
              std::vector<types::point_t> relativeOutlinePoints);
  ~VoronoiCell() override;

public:
  bool isTargetable() const override;
  bool isSelectable() const override;

public:
  const types::polygon_t &getPolygon() const;
  const types::box_t &getEnvelope() const;
  const std::vector<types::point_t> &getOutlinePoints() const;
  const std::vector<types::point_t> &getRelativeOutlinePoints() const;
  const std::vector<types::segment_t> &getOutlineSegments() const;
  const Tile &getTile() const;
  Tile &getTile();
  std::shared_ptr<Tile> getTilePtr();

private:
  types::graph_vertex_desc_t vertexDesc;
  std::vector<types::point_t> outlinePoints;
  std::vector<types::point_t> relativeOutlinePoints;
  types::polygon_t polygon;
  types::box_t envelope;
  std::vector<types::segment_t> outlineSegments;
  std::shared_ptr<Tile> tilePtr;
};

} // namespace model
} // namespace how
#endif // VORONOICELL_H
