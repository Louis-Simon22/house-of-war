#include "worldbuilder.h"

#include "../../../utils/algo/poissondisksamplingpointsgenerator.h"
#include "../cell.h"
#include "../../../utils/algo/fortune/fortune.h"
#include <QDebug>

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
//    const auto& fortune = new Fortune(points);
//    fortune->sweep();
    return new WorldModel(cells);
}
