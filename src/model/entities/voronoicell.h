#ifndef VORONOICELL_H
#define VORONOICELL_H

#include <memory>

#include "../modeltypes.h"
#include "./tile.h"

namespace how {
namespace model {

class VoronoiCell : public Entity {
public:
  VoronoiCell();
  VoronoiCell(types::box_t envelope, types::point_t centroid,
              types::polygon_t polygon,
              std::vector<types::point_t> outlinePoints,
              std::vector<types::segment_t> outlineSegments);
  ~VoronoiCell() override;

public:
  const types::box_t &getEnvelope() const;
  const types::point_t &getCentroid() const;
  const types::polygon_t &getPolygon() const;
  const std::vector<types::point_t> &getOutlinePoints() const;
  const std::vector<types::segment_t> &getOutlineSegments() const;
  const Tile &getTile() const;
  Tile &getTile();

private:
  types::box_t envelope;
  types::point_t centroid;
  types::polygon_t polygon;
  std::vector<types::point_t> outlinePoints;
  std::vector<types::segment_t> outlineSegments;
  Tile tile;
};

} // namespace model
} // namespace how
#endif // VORONOICELL_H
