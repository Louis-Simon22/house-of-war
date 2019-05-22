#ifndef VORONOICELL_H
#define VORONOICELL_H

#include <vector>

#include "./tile.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
} // namespace

class VoronoiCell : public GraphEntity {
public:
  VoronoiCell(types::point_t center, std::vector<types::point_t> outlinePoints);
  ~VoronoiCell() override;

public:
  bool isTargetable() const override;
  bool isSelectable() const override;
  bool isWithinSelectionArea(types::coordinate_t posX,
                          types::coordinate_t posY) const override;

public:
  const types::polygon_t &getPolygon() const;
  const types::box_t &getEnvelope() const;
  const std::vector<types::point_t> &getOutlinePoints() const;
  const std::vector<types::segment_t> &getOutlineSegments() const;
  const Tile &getTile() const;
  Tile &getTile();

private:
  std::vector<types::point_t> outlinePoints;
  types::polygon_t polygon;
  types::box_t envelope;
  std::vector<types::segment_t> outlineSegments;
  std::shared_ptr<Tile> tilePtr;
};

} // namespace model
} // namespace how
#endif // VORONOICELL_H
