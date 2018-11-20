#ifndef WORLDBUILDER_H
#define WORLDBUILDER_H

#include <QRandomGenerator>
#include <QVector2D>

#include <QRect>
#include "../worldmodel.h"
#include <boost/geometry.hpp>

namespace bg = boost::geometry;
using Point = bg::model::point<long, 2, bg::cs::cartesian>;

class WorldBuilder {
 public:
  WorldBuilder();

  WorldBuilder* setSourcesCount(int sourcesCount);
  WorldBuilder* setWorldDimensions(int width, int height);
  WorldModel* build() const;

  QRandomGenerator* random;
  int sourcesCount;
  QRect worldDimensions;

 private:
};

#endif
