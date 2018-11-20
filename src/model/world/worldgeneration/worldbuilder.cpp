#include "worldbuilder.h"

#include <iostream>
#include "../../../utils/algo/poissondisksampling.h"
#include "../cell.h"

WorldBuilder::WorldBuilder() { this->random = QRandomGenerator::global(); }

WorldBuilder* WorldBuilder::setSourcesCount(int sourcesCount) {
  this->sourcesCount = sourcesCount;
  return this;
}

WorldBuilder* WorldBuilder::setWorldDimensions(int width, int height) {
  this->worldDimensions = QRect(0, 0, width, height);
  return this;
}

WorldModel* WorldBuilder::build() const {
  const auto& min_corner = Point(0, 0);
  const auto& max_corner = Point(500, 500);
  auto const generator =
      ::how::algo::PoissonDiskSampling<Point>(min_corner, max_corner, 50, 100, 40);
  auto const& points = generator.generateSequence();
  return new WorldModel(nullptr);
}
