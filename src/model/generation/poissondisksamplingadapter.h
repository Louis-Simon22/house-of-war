#ifndef POISSONDISKSAMPLINGADAPTER_H
#define POISSONDISKSAMPLINGADAPTER_H

#include "../modeltypes.h"

namespace how {
namespace model {

std::vector<types::point_t> generatePoissonDiskSamplingByMinimumDistance(
    types::coordinate_t minimumDistance, types::box_t bounds,
    std::uint32_t maxAttempts, std::uint32_t seed);

std::vector<types::point_t>
generatePoissonDiskSamplingByApproximateNumberOfPoints(
    std::uint32_t numberOfPoints, types::box_t bounds,
    std::uint32_t maxAttempts, std::uint32_t seed);
} // namespace model
} // namespace how

#endif // POISSONDISKSAMPLING_H
