#ifndef PAINTERUTILS_H
#define PAINTERUTILS_H

#include <vector>

#include "../../model/modeltypes.h"

namespace how {
namespace ui {
namespace utils {

std::vector<types::point_t>
getRectanglePointsClockwise(float x, float y, float width, float height);

std::vector<types::point_t> getCirclePoints(float x, float y, float radius);

std::vector<types::point_t>
getPointsFromSegments(const std::vector<types::segment_t> &segments);

std::vector<types::point_t>
getPointsRelativeTo(float originX, float originY,
                    const std::vector<types::point_t> &points);

} // namespace utils
} // namespace ui
} // namespace how

#endif // PAINTERUTILS_H
