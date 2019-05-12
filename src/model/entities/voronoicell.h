#ifndef VORONOICELL_H
#define VORONOICELL_H

#include <vector>

#include "./graphentity.h"
#include "./tile.h"

namespace how {
namespace model {

class VoronoiCell : public GraphEntity {
public:
  static constexpr types::layer_t VORONOI_CELL_LAYER = 0;

public:
  VoronoiCell();
  VoronoiCell(types::box_t envelope, types::point_t center, types::polygon_t polygon,
              std::vector<types::point_t> outlinePoints,
              std::vector<types::segment_t> outlineSegments);
  ~VoronoiCell() override;

public:
  types::coordinate_t getPosX() const override;
  types::coordinate_t getPosY() const override;
  types::coordinate_t getWidth() const override;
  types::coordinate_t getHeight() const override;
  bool isTargetable() const override;
  bool isSelectable() const override;

public:
  const types::box_t &getEnvelope() const;
  const types::point_t &getCenter() const;
  const types::polygon_t& getPolygon() const;
  const std::vector<types::point_t> &getOutlinePoints() const;
  const std::vector<types::segment_t> &getOutlineSegments() const;
  const Tile &getTile() const;
  Tile &getTile();

private:
  types::box_t envelope;
  types::point_t center;
  types::polygon_t polygon;
  std::vector<types::point_t> outlinePoints;
  std::vector<types::segment_t> outlineSegments;
  Tile tile;
};

} // namespace model
} // namespace how
#endif // VORONOICELL_H
