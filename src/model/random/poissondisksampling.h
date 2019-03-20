#ifndef POISSONDISKSAMPLINGPOINTSGENERATOR_H
#define POISSONDISKSAMPLINGPOINTSGENERATOR_H

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/strategies/strategies.hpp>
#include <boost/multi_array.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "../random/utilsrandom.h"

namespace how {
namespace model {
namespace {
namespace bg = ::boost::geometry;
}

namespace {

template <typename point_t, typename coordinate_t, std::size_t DimensionIndex>
struct Coordinates {
  static void coordinatesToVector(const point_t &point,
                                  std::vector<coordinate_t> &coordinates) {
    coordinates[DimensionIndex - 1] = bg::get<DimensionIndex - 1>(point);
    Coordinates<point_t, coordinate_t, DimensionIndex - 1>::coordinatesToVector(
        point, coordinates);
  }
  static void vectorToCoordinates(const std::vector<coordinate_t> &coordinates,
                                  point_t &point) {
    bg::set<DimensionIndex - 1>(point, coordinates[DimensionIndex - 1]);
    Coordinates<point_t, coordinate_t, DimensionIndex - 1>::vectorToCoordinates(
        coordinates, point);
  }
};

template <typename point_t, typename coordinate_t>
struct Coordinates<point_t, coordinate_t, 0> {
  static void coordinatesToVector(const point_t &,
                                  std::vector<coordinate_t> &) {
    // Stops recursion
  }
  static void vectorToCoordinates(const std::vector<coordinate_t> &,
                                  point_t &) {
    // Stops recursion
  }
};

// TODO maybe replace this with
// https://www.boost.org/doc/libs/1_69_0/boost/geometry/util/for_each_coordinate.hpp
template <typename point_t, typename coordinate_t, std::size_t DimensionIndex>
struct PointConverter {
  static std::vector<coordinate_t> toVector(const point_t &point) {
    auto coordinates = std::vector<coordinate_t>(DimensionIndex);
    Coordinates<point_t, coordinate_t, DimensionIndex>::coordinatesToVector(
        point, coordinates);
    return coordinates;
  }
  static point_t fromVector(const std::vector<coordinate_t> &coordinates) {
    auto point = point_t();
    Coordinates<point_t, coordinate_t, DimensionIndex>::vectorToCoordinates(
        coordinates, point);
    return point;
  }
};

template <typename point_t, typename coordinate_t, std::size_t DimensionCount>
class BackgroundGrid {
  BOOST_CONCEPT_ASSERT((bg::concepts::Point<point_t>));
  using multi_array_t = boost::multi_array<point_t, DimensionCount>;
  using point_converter_t =
      PointConverter<point_t, coordinate_t, DimensionCount>;
  using range_t = boost::multi_array_types::index_range;

private:
  multi_array_t grid;
  point_t nullPoint;
  std::vector<std::size_t> extents;
  coordinate_t cellWidth;

  BackgroundGrid(std::vector<std::size_t> extents, coordinate_t cellWidth,
                 point_t nullPoint)
      : grid(extents), nullPoint(nullPoint), extents(extents),
        cellWidth(cellWidth) {
    std::fill_n(this->grid.data(), this->grid.num_elements(), nullPoint);
  }

public:
  static BackgroundGrid<point_t, coordinate_t, DimensionCount>
  create(point_t min_corner, point_t max_corner,
         coordinate_t minimumPointDistance) {
    auto minCornerAsVector = point_converter_t::toVector(min_corner);
    const auto &maxCornerAsVector = point_converter_t::toVector(max_corner);

    auto extents = std::vector<std::size_t>(DimensionCount);
    for (int i = 0; i < DimensionCount; i++) {
      const double distance = maxCornerAsVector[i] - minCornerAsVector[i];
      extents[i] = ceil(distance / minimumPointDistance);
    }

    auto nullPoint = min_corner;
    bg::subtract_value<>(nullPoint, 1);
    return BackgroundGrid<point_t, coordinate_t, DimensionCount>(
        extents, minimumPointDistance, nullPoint);
  }

  void insertPointInBackgroundGrid(point_t point) {
    const auto &indices = BackgroundGrid::getPointIndices(point);
    this->grid(indices) = point;
  }

  bool pointIsFarEnoughFromAdjacent(point_t point,
                                    coordinate_t minimumDistance) {
    auto indices = BackgroundGrid::getPointIndices(point);
    if (!bg::equals(this->grid(indices), this->nullPoint)) {
      // Cell is occupied
      return false;
    } else {
      const auto &adjacentPoints = this->getAdjacentPoints(indices);
      for (int i = 0; i < adjacentPoints.size(); i++) {
        auto distance = bg::distance(point, adjacentPoints[i]);
        if (distance < minimumDistance) {
          return false;
        }
      }
      return true;
    }
  }

  std::vector<point_t> getAdjacentPoints(std::vector<std::size_t> indices) {
    auto adjacentPointsList = std::vector<point_t>();

    getAdjacentPointsRec(adjacentPointsList, indices, 0);

    return adjacentPointsList;
  }

private:
  void getAdjacentPointsRec(std::vector<point_t> &adjacentPointsList,
                            std::vector<std::size_t> indices,
                            std::size_t dimensionIndex) {
    if (dimensionIndex < DimensionCount) {
      for (std::size_t index =
               indices[dimensionIndex] > 0 ? indices[dimensionIndex] - 1 : 0;
           index <= std::min(this->extents[dimensionIndex] - 1,
                             indices[dimensionIndex] + 1);
           index++) {
        indices[dimensionIndex] = index;
        getAdjacentPointsRec(adjacentPointsList, indices, dimensionIndex + 1);
      }
    } else {
      const auto &point = this->grid(indices);
      if (!bg::equals(point, this->nullPoint)) {
        adjacentPointsList.push_back(point);
      }
    }
  }

  std::vector<std::size_t> getPointIndices(point_t point) {
    const auto &pointAsVector = point_converter_t::toVector(point);
    auto indices = std::vector<std::size_t>(DimensionCount);

    for (long i = 0; i < DimensionCount; i++) {
      indices[i] = floor(pointAsVector[i] / this->cellWidth);
    }

    return indices;
  }
};
} // namespace

template <typename point_t> class PoissonDiskSampling {
  BOOST_CONCEPT_ASSERT((bg::concepts::Point<point_t>));
  constexpr static std::size_t DIMENSION_COUNT =
      bg::traits::dimension<point_t>::value;
  using box_t = bg::model::box<point_t>;
  using coordinate_t = typename bg::traits::coordinate_type<point_t>::type;
  using background_grid_t =
      BackgroundGrid<point_t, coordinate_t, DIMENSION_COUNT>;
  using point_converter_t =
      PointConverter<point_t, coordinate_t, DIMENSION_COUNT>;
  using random_generator_t = ::boost::random::mt19937;

private:
  background_grid_t backgroundGrid;
  box_t boundingBox;
  coordinate_t minimumPointDistance;
  coordinate_t maximumGenerationAttempts;
  random_generator_t generator;

public:
  PoissonDiskSampling(point_t min_corner, point_t max_corner,
                      coordinate_t maximumGenerationAttempts,
                      coordinate_t minimumPointDistance)
      : backgroundGrid(background_grid_t::create(min_corner, max_corner,
                                                 minimumPointDistance)),
        boundingBox(box_t(min_corner, max_corner)),
        minimumPointDistance(minimumPointDistance),
        maximumGenerationAttempts(maximumGenerationAttempts) {}

  std::vector<point_t> generateSequence() {
    const auto &initialPoint = this->getRandomPointInBox(
        this->generator, this->boundingBox.min_corner(),
        this->boundingBox.max_corner());
    // TODO initialize the lists with an approximate size
    auto generatedPoints = std::vector<point_t>();
    auto activePoints = std::vector<point_t>();
    generatedPoints.push_back(initialPoint);
    activePoints.push_back(initialPoint);

    this->backgroundGrid.insertPointInBackgroundGrid(initialPoint);
    while (!activePoints.empty()) {
      const auto &randomActiveListIndex =
          intInRange<random_generator_t, std::size_t>(this->generator, 0,
                                                      activePoints.size());
      bool isPointValid = false;
      for (std::size_t i = 0;
           i < this->maximumGenerationAttempts && !isPointValid; i++) {
        auto randomPointInAnnulus =
            PoissonDiskSampling::getRandomPointInAnnulus(
                this->generator, activePoints[randomActiveListIndex],
                this->minimumPointDistance, this->minimumPointDistance * 2);

        isPointValid = bg::within<point_t, box_t>(randomPointInAnnulus,
                                                  this->boundingBox) &&
                       this->backgroundGrid.pointIsFarEnoughFromAdjacent(
                           randomPointInAnnulus, this->minimumPointDistance);

        if (isPointValid) {
          generatedPoints.push_back(randomPointInAnnulus);
          activePoints.push_back(randomPointInAnnulus);
          this->backgroundGrid.insertPointInBackgroundGrid(
              randomPointInAnnulus);
        }
      }

      if (!isPointValid) {
        activePoints.erase(activePoints.begin() + randomActiveListIndex);
      }
    }

    return generatedPoints;
  }

private:
  static point_t getRandomPointInAnnulus(random_generator_t &generator,
                                         point_t center, coordinate_t innerR,
                                         coordinate_t outerR) {
    coordinate_t distance;
    point_t randomPoint;
    do {
      auto minCorner = center;
      bg::subtract_value<>(minCorner, outerR);
      auto maxCorner = center;
      bg::add_value<>(maxCorner, outerR);
      randomPoint = PoissonDiskSampling::getRandomPointInBox(
          generator, minCorner, maxCorner);
      distance = bg::distance(randomPoint, center);
    } while (distance < innerR || distance > outerR);
    return randomPoint;
  }

  static point_t getRandomPointInBox(random_generator_t &generator,
                                     point_t min_corner, point_t max_corner) {
    const auto &minCornerAsVector = point_converter_t::toVector(min_corner);
    const auto &maxCornerAsVector = point_converter_t::toVector(max_corner);
    auto randomPointAsVector = std::vector<coordinate_t>(DIMENSION_COUNT);

    for (long i = 0; i < DIMENSION_COUNT; i++) {
      randomPointAsVector[i] = intInRange<random_generator_t, coordinate_t>(
          generator, minCornerAsVector[i], maxCornerAsVector[i]);
    }

    return point_converter_t::fromVector(randomPointAsVector);
  }
};
} // namespace model
} // namespace how

#endif // POISSONDISKSAMPLINGPOINTSGENERATOR_H
