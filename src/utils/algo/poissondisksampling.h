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

#include <iostream>

namespace how {
namespace algo {

namespace {

namespace bg = ::boost::geometry;

template <typename point_t, typename coordinate_t, std::size_t DimensionIndex>
struct OneDimensional {
  static void distance(point_t min, point_t max,
                       std::vector<coordinate_t> distances) {
    distances.push_back(bg::get<DimensionIndex>(max) -
                        bg::get<DimensionIndex>(min));
    OneDimensional<point_t, coordinate_t, DimensionIndex - 1>::distance(min, max, distances);
  }
};

template<typename point_t, typename coordinate_t>
struct OneDimensional<point_t, coordinate_t, 0> {
  static void distance(point_t, point_t, std::vector<coordinate_t>) {
    // Stops recursion
  }
};

template <typename point_t, std::size_t DimensionCount>
class BackgroundGrid {
  BOOST_CONCEPT_ASSERT((bg::concepts::Point<point_t>));
//  using coordinate_t =
//  typename bg::traits::coordinate_type<typename remove_cv<point_t>::type>;
  using coordinate_t =
  bg::traits::dimension<point_t>;

 private:
  boost::multi_array<point_t, DimensionCount> grid;
  BackgroundGrid(boost::multi_array<point_t, DimensionCount> grid)
      : grid(grid) {}

 public:
  static BackgroundGrid<point_t, DimensionCount> create(point_t min_corner,
                                                        point_t max_corner) {
    auto distances = std::vector<coordinate_t>();
    OneDimensional<point_t, coordinate_t, DimensionCount - 1>::distance(
        min_corner, max_corner, distances);
    auto grid = boost::multi_array<point_t, DimensionCount>();
    for (unsigned long i = 0; i < distances.size(); i++) {
      //        std::cout << distances[i];
    }
    auto bgrid = BackgroundGrid<point_t, DimensionCount>(grid);
    return bgrid;
  }
};
}  // namespace

template <typename point_t>
class PoissonDiskSampling {
  BOOST_CONCEPT_ASSERT((bg::concepts::Point<point_t>));
  using Box = bg::model::box<point_t>;
  using coordinate_t = typename bg::traits::coordinate_type<point_t>;

 private:
  constexpr static coordinate_t DIMENSION_COUNT =
      bg::traits::dimension<point_t>::value;
  BackgroundGrid<point_t, DIMENSION_COUNT> backgroundGrid;
  Box boundingBox;
  float minimumPointDistance;
  float maximumPointDistance;
  long maximumGenerationAttempts;
  ::boost::random::mt19937 gen;
  std::function<long(::boost::random::mt19937)> greg;

 public:
  PoissonDiskSampling(point_t min_corner, point_t max_corner,
                      long minimumPointDistance, long maximumPointDistance,
                      long maximumGenerationAttempts)
      : minimumPointDistance(minimumPointDistance),
        maximumPointDistance(maximumPointDistance),
        maximumGenerationAttempts(maximumGenerationAttempts),
        boundingBox(Box(min_corner, max_corner)),
        backgroundGrid(BackgroundGrid<point_t, DIMENSION_COUNT>::create(
            min_corner, max_corner)) {}

  std::vector<point_t> generateSequence() {
    const auto& initialPoint = point_t(50, 50);
    // TODO initialize the lists with an approximate size
    auto generatedPoints = std::vector<point_t>();
    auto activePoints = std::vector<point_t>();
    generatedPoints.push_back(initialPoint);
    activePoints.push_back(initialPoint);

    //    long backgroundYIndex =
    //    this->pointToBackgroundGridYIndex(initialPoint); long backgroundXIndex
    //    = this->pointToBackgroundGridXIndex(initialPoint);
    //    this->backgroundGrid[backgroundYIndex][backgroundXIndex] =
    //    initialPoint; int limit = 0; while (!activePoints.isEmpty() && ++limit
    //    < 3000) {
    //      long randomActiveListIndex = this->random.bounded(0,
    //      activePoints.size()); bool isPointValid = false; for (long i = 0; i
    //      < this->maximumGenerationAttempts && !isPointValid;
    //           i++) {
    //        QVector2D randomPointInAnnulus = this->randomPointInAnnulus(
    //            activePoints.at(randomActiveListIndex),
    //            this->minimumPointDistance, this->minimumPointDistance
    //            * 2.0f);
    //        long pointBackgroundGridYIndex =
    //            this->pointToBackgroundGridYIndex(randomPointInAnnulus);
    //        long pointBackgroundGridXIndex =
    //            this->pointToBackgroundGridXIndex(randomPointInAnnulus);

    //        bool isPointValid =
    //            this->areaDimensions.contains(randomPointInAnnulus.x(),
    //                                          randomPointInAnnulus.y(), true)
    //                                          &&
    //            this->pointIsFarEnoughFromOthers(pointBackgroundGridYIndex,
    //                                             pointBackgroundGridXIndex,
    //                                             randomPointInAnnulus);
    //        if (isPointValid) {
    //          generatedPoints.append(randomPointInAnnulus);
    //          activePoints.append(randomPointInAnnulus);
    //          this->backgroundGrid[pointBackgroundGridYIndex]
    //                              [pointBackgroundGridXIndex] =
    //              randomPointInAnnulus;
    //        }
    //      }

    //      if (!isPointValid) {
    //        activePoints.remove(randomActiveListIndex);
    //      }
    //    }

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
//    for (long i = -2; i <= 2; i++) {
//      long modY = pointBackgroundGridYIndex + i;
//      for (long j = -2; j <= 2; j++) {
//        long modX = pointBackgroundGridXIndex + j;

//        if (modY >= 0 && modX >= 0 && modY < this->backgroundGridDimensionY &&
//            modX < this->backgroundGridDimensionX) {
//          QVector2D otherPoint = this->backgroundGrid.at(modY).at(modX);

//          if (otherPoint != this->nullVector &&
//              point.distanceToPoint(otherPoint) < this->minimumPointDistance) {
//            return false;
//          }
//        }
//      }
//    }

    return true;
  }
};
}  // namespace algo
}  // namespace how

#endif  // POISSONDISKSAMPLINGPOINTSGENERATOR_H
