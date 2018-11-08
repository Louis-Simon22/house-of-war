#include "worldbuilder.h"

#include "../../../utils/algo/poissondisksamplingpointsgenerator.h"
#include "../cell.h"
#include <QDebug>

#include <boost/geometry/geometries/point_xy.hpp>

using namespace boost::geometry::model::d2;

WorldBuilder::WorldBuilder()
{
    this->random = QRandomGenerator::global();
}

WorldBuilder* WorldBuilder::setSourcesCount(int sourcesCount)
{
    this->sourcesCount = sourcesCount;
    return this;
}

WorldBuilder* WorldBuilder::setWorldDimensions(int width, int height)
{
    this->worldDimensions = QRect(0, 0, width, height);
    return this;
}

WorldModel* WorldBuilder::build() const
{
    PoissonDiskSamplingPointsGenerator generator = PoissonDiskSamplingPointsGenerator(this->worldDimensions, 50, 40);
    QVector<QVector2D> points = generator.generateSequence();
    QVector<Cell*>* cells = new QVector<Cell*>(points.size());
    for(int i = 0; i < points.size(); i++)
    {
        cells->replace(i, new Cell(points[i]));
    }
    const auto& point = point_xy<long>(0, 0);
    return new WorldModel(cells);
}
