#ifndef POISSONDISKSAMPLINGPOINTSGENERATOR_H
#define POISSONDISKSAMPLINGPOINTSGENERATOR_H

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/multi_array.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <functional>

namespace how {
namespace algo {

namespace bg = ::boost::geometry;

template <typename point_t, std::size_t DimensionCount>
class BackgroundGrid;

template <typename point_t>
class PoissonDiskSampling {
  BOOST_CONCEPT_ASSERT((bg::concepts::Point<point_t>));
  using Box = bg::model::box<point_t>;

 private:
  BackgroundGrid<
      point_t, bg::traits::dimension<typename remove_cv<point_t>::type>::value>
      backgroundGrid;
  Box boundingBox;
  float minimumPointDistance;
  float maximumPointDistance;
  long maximumGenerationAttempts;
  ::boost::random::mt19937 gen;
  std::function<long(::boost::random::mt19937)> greg;

 public:
  PoissonDiskSampling(point_t min_corner, point_t max_corner,
                      long minimumPointDistance, long maximumPointDistance,
                      long maximumGenerationAttempts) {
    this->boundingBox = Box(min_corner, max_corner);
    this->minimumPointDistance = minimumPointDistance;
    this->maximumPointDistance = maximumPointDistance;
    this->maximumGenerationAttempts = maximumGenerationAttempts;
    ::boost::random::uniform_int_distribution<> dist(1, 6);
    this->greg = dist;

    this->initializeBackgroundGrid();
  }

  std::vector<point_t> generateSequence() {
    const auto& initialPoint = point_t(
        randomBoundedFloat(this->random, (float)this->areaDimensions.left(),
                           (float)this->areaDimensions.right()),
        randomBoundedFloat(this->random, (float)this->areaDimensions.top(),
                           (float)this->areaDimensions.bottom()));
    // TODO initialize the lists with an approximate size
    const auto generatedPoints = std::vector<point_t>();
    const auto activePoints = std::vector<point_t>();
    generatedPoints.push_back(initialPoint);
    activePoints.push_back(initialPoint);

    long backgroundYIndex = this->pointToBackgroundGridYIndex(initialPoint);
    long backgroundXIndex = this->pointToBackgroundGridXIndex(initialPoint);
    this->backgroundGrid[backgroundYIndex][backgroundXIndex] = initialPoint;
    int limit = 0;
    while (!activePoints.isEmpty() && ++limit < 3000) {
      long randomActiveListIndex = this->random.bounded(0, activePoints.size());
      bool isPointValid = false;
      for (long i = 0; i < this->maximumGenerationAttempts && !isPointValid;
           i++) {
        QVector2D randomPointInAnnulus = this->randomPointInAnnulus(
            activePoints.at(randomActiveListIndex), this->minimumPointDistance,
            this->minimumPointDistance * 2.0f);
        long pointBackgroundGridYIndex =
            this->pointToBackgroundGridYIndex(randomPointInAnnulus);
        long pointBackgroundGridXIndex =
            this->pointToBackgroundGridXIndex(randomPointInAnnulus);

        bool isPointValid =
            this->areaDimensions.contains(randomPointInAnnulus.x(),
                                          randomPointInAnnulus.y(), true) &&
            this->pointIsFarEnoughFromOthers(pointBackgroundGridYIndex,
                                             pointBackgroundGridXIndex,
                                             randomPointInAnnulus);
        if (isPointValid) {
          generatedPoints.append(randomPointInAnnulus);
          activePoints.append(randomPointInAnnulus);
          this->backgroundGrid[pointBackgroundGridYIndex]
                              [pointBackgroundGridXIndex] =
              randomPointInAnnulus;
        }
      }

      if (!isPointValid) {
        activePoints.remove(randomActiveListIndex);
      }
    }

    return generatedPoints;
  }

 private:
  long pointToBackgroundGridYIndex(point_t point) {
    return ceil((point.y() - this->areaDimensions.y()) /
                this->minimumPointDistance);
  }

  point_t randomPointInAnnulus(point_t point, float innerR, float outerR) {
    float randomAngle = 2 * M_PI * this->random.generateDouble();
    float randomRadius =
        ((outerR - innerR) * this->random.generateDouble()) + innerR;
    float xTranslationFromCenter = randomRadius * cos(randomAngle);
    float yTranslationFromCenter = randomRadius * sin(randomAngle);
    return QVector2D(point.x() + xTranslationFromCenter,
                     point.y() + yTranslationFromCenter);
  }

  bool pointIsFarEnoughFromOthers(long pointBackgroundGridYIndex,
                                  long pointBackgroundGridXIndex,
                                  point_t point) {
    for (long i = -2; i <= 2; i++) {
      long modY = pointBackgroundGridYIndex + i;
      for (long j = -2; j <= 2; j++) {
        long modX = pointBackgroundGridXIndex + j;

        if (modY >= 0 && modX >= 0 && modY < this->backgroundGridDimensionY &&
            modX < this->backgroundGridDimensionX) {
          QVector2D otherPoint = this->backgroundGrid.at(modY).at(modX);

          if (otherPoint != this->nullVector &&
              point.distanceToPoint(otherPoint) < this->minimumPointDistance) {
            return false;
          }
        }
      }
    }

    return true;
  }
};

namespace {
template <typename point_t, std::size_t DimensionCount>
class BackgroundGrid {
  BOOST_CONCEPT_ASSERT((bg::concepts::Point<point_t>));

 private:
  boost::multi_array<point_t, DimensionCount> grid;

  template <std::size_t GridDimensionCount>
  static BackgroundGrid create(point_t min_corner, point_t max_corner) {
    auto const grid = boost::multi_array<point_t, GridDimensionCount>();
    oneDimensionalDistance<GridDimensionCount>(min_corner, max_corner, grid);
  }

  template <std::size_t Dimension>
  static void oneDimensionalDistance(
      point_t min, point_t max,
      boost::multi_array<point_t, DimensionCount>& grid) {
    grid[Dimension - 1] = bg::get(max, Dimension) - bg::get(min, Dimension);
    oneDimensionalDistance<Dimension - 1>(min, max, grid);
  }
};

// TODO specific specialization also require containing class to be specialize. Need workaround
template <>
static inline void BackgroundGrid::oneDimensionalDistance<0>(
    point_t min, point_t max,
    boost::multi_array<point_t, DimensionCount>& grid) {
  // Stops recursion
}
}  // namespace
}  // namespace algo
}  // namespace how

#endif  // POISSONDISKSAMPLINGPOINTSGENERATOR_H
