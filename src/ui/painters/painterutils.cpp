#include "painterutils.h"

#include <math.h>

namespace how {
namespace ui {
namespace utils {
namespace {
namespace bg = ::boost::geometry;
}

std::vector<types::point_t>
getRectanglePointsClockwise(float x, float y, float width, float height) {
  auto halfwidth = width / 2;
  auto halfheight = height / 2;
  return {types::point_t(x - halfwidth, y - halfheight),
          types::point_t(x + halfwidth, y - halfheight),
          types::point_t(x + halfwidth, y + halfheight),
          types::point_t(x - halfwidth, y + halfheight)};
}

std::vector<types::point_t> getCirclePoints(float x, float y, float radius) {
  auto pointsCount = 50 + static_cast<std::size_t>(radius) * 2;
  auto points = std::vector<types::point_t>();
  points.reserve(pointsCount);
  auto angleStep = static_cast<float>(2 * M_PI / pointsCount);

  for (std::size_t i = 0; i < static_cast<std::size_t>(pointsCount); i++) {
    auto angle = i * angleStep;
    points.push_back(
        types::point_t(x + radius * cos(angle), y + radius * sin(angle)));
  }

  return points;
}

std::vector<types::point_t>
getPointsFromSegments(const std::vector<types::segment_t> &segments) {
  auto points = std::vector<types::point_t>();
  points.reserve(segments.size() * 2);

  for (auto &segment : segments) {
    points.push_back(segment.first);
    points.push_back(segment.second);
  }

  return points;
}

} // namespace utils
} // namespace ui
} // namespace how
