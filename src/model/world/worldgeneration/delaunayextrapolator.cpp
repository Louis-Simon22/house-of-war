#include "delaunayextrapolator.h"

#include "../../segmentcomparator.h"

namespace how {
namespace model {
DelaunayExtrapolator::DelaunayExtrapolator() {}

types::delaunayGraph DelaunayExtrapolator::extrapolateDelaunayTriangulation(
    std::vector<VoronoiCell> voronoiCells) {
  auto delaunayGraph = types::delaunayGraph();
  auto cellsBySegment =
      std::map<types::segment_t, VoronoiCell, SegmentComparator>();

  for (const auto &voronoiCell : voronoiCells) {
    for (const auto &segment : voronoiCell.segments) {
      const auto &foundSegmentIt = cellsBySegment.find(segment);
      if (foundSegmentIt == cellsBySegment.end()) {
        cellsBySegment[segment] = voronoiCell;
      } else {
        const auto &foundSegment = *foundSegmentIt;

      }
    }
  }

  return delaunayGraph;
}
} // namespace model
} // namespace how
