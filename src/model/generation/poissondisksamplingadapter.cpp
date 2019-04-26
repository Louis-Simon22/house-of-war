#include "poissondisksamplingadapter.h"

#include <math.h>

#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/strategies/strategies.hpp>
#include <boost/math/special_functions/pow.hpp>

#include "../../../lib/poisson-disk-sampling/include/thinks/poisson_disk_sampling/poisson_disk_sampling.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
namespace pds = ::thinks::poisson_disk_sampling;
namespace bm = ::boost::math;

std::array<float, 2> convert(types::point_t point) {
  auto convertedPoint = std::array<float, 2>();
  convertedPoint[0] = bg::get<0>(point);
  convertedPoint[1] = bg::get<1>(point);
  return convertedPoint;
}
} // namespace

std::vector<types::point_t> generatePoissonDiskSamplingByMinimumDistance(
    types::coordinate_t minimumDistance, types::box_t bounds,
    std::uint32_t maxAttempts, std::uint32_t seed) {
  const auto &boundsMin = convert(bounds.min_corner());
  const auto &boundsMax = convert(bounds.max_corner());

  const auto &points = pds::PoissonDiskSampling(minimumDistance, boundsMin,
                                                boundsMax, maxAttempts, seed);

  auto convertedPoints = std::vector<types::point_t>();
  for (const auto &point : points) {
    convertedPoints.push_back(types::point_t(point[0], point[1]));
  }

  return convertedPoints;
}

std::vector<types::point_t>
generatePoissonDiskSamplingByApproximateNumberOfPoints(
    std::uint32_t numberOfPoints, types::box_t bounds,
    std::uint32_t maxAttempts, std::uint32_t seed) {
  // https://math.stackexchange.com/questions/2548513/maximum-number-of-circle-packing-into-a-rectangle
  const auto triangularPackingLimitDensity = M_PI / (2 * sqrt(3));
  const auto area = bg::area(bounds);
  const auto estimatedUsableArea = area * triangularPackingLimitDensity;
  const auto estimatedAreaSide = sqrt(estimatedUsableArea);
  const auto estimatedCellSize = estimatedAreaSide / sqrt(numberOfPoints);
  return generatePoissonDiskSamplingByMinimumDistance(
      static_cast<float>(estimatedCellSize), bounds, maxAttempts, seed);
}

} // namespace model
} // namespace how
