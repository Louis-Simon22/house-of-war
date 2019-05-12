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
  VoronoiCell(types::box_t envelope, std::vector<types::point_t> outlinePoints,
              std::vector<types::segment_t> outlineSegments);
  ~VoronoiCell() override;

public:
  const types::box_t &getEnvelope() const;
  const std::vector<types::point_t> &getOutlinePoints() const;
  const std::vector<types::segment_t> &getOutlineSegments() const;
  const Tile &getTile() const;
  Tile &getTile();

private:
  types::box_t envelope;
  std::vector<types::point_t> outlinePoints;
  std::vector<types::segment_t> outlineSegments;
  Tile tile;
};

} // namespace model
} // namespace how
#endif // VORONOICELL_H
